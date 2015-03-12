#include "Primitive.h"

#include <MathLib/Vector3d.h>
#include <algorithm>

bool PointPrimitive::intersectSegments( Point3d& start1, Point3d& end1, Point3d& start2, Point3d& end2, Point3d& intersection ) {

	Vector3d vec1 = end1 - start1;
	Vector3d vec2 = end2 - start2;

	Vector3d testVec = start2 - start1;

	double denom =  vec2.x * vec1.y - vec1.x * vec2.y;
	if( denom != 0 ) {
		double invDenom = 1.0 / denom;
		double h = (vec2.x * testVec.y - testVec.x * vec2.y) * invDenom;
		if( h > 0 && h < 1 ) {
			double h2 = (vec1.x * testVec.y - testVec.x * vec1.y) * invDenom;
			if( h2 > 0 && h2 < 1 ) {
				intersection =  start1 + vec1 * h;
				return true;
			}
		}
	}
	return false;
}




void PolygonPrimitive::makeCCW() {
	if( volume() < 0 )
		std::reverse( points.begin(), points.end() );
}

// Returns a signed volume: 
// Negative = CW, 
// Positive = CCW
double PolygonPrimitive::volume() {
	// Using Green's theorem in a plane

	int size = points.size();

	double area = 0;
	for( int i=0; i<size; ++i ) {
		int nextI = (i+1)%size;
		area += points[i].x * points[nextI].y - points[nextI].x * points[i].y;
	}
	return area / 2.0;
}

Point3d PolygonPrimitive::midPoint() {

	int size = points.size();

	Point3d midPoint(0,0,0);

	if( size == 0 )
		return midPoint;

	for( int i=0; i<size; ++i ) {
		midPoint += points[i];
	}
	midPoint.x /= size;
	midPoint.y /= size;

	return midPoint;
}



#if 0


// Code from http://tog.acm.org/GraphicsGems//gemsiv/ptpoly_haines/ptinpoly.c
bool PolygonPrimitive::isPointInside( Point3d& point ) {
	
	register int	j, yflag0, yflag1, inside_flag, xflag0 ;
	register double ty, tx;
	register Point3d *vtx0, *vtx1 ;

    tx = point.x ;
    ty = point.y ;

    vtx0 = &points.back();
    /* get test bit for above/below X axis */
    yflag0 = ( vtx0->y >= ty ) ;
    vtx1 = &points.front();

	int numverts = points.size();
    inside_flag = 0 ;
    for ( j = numverts+1 ; --j ; ) {

	yflag1 = ( vtx1->y >= ty ) ;
	/* check if endpoints straddle (are on opposite sides) of X axis
	 * (i.e. the Y's differ); if so, +X ray could intersect this edge.
	 */
	if ( yflag0 != yflag1 ) {
	    xflag0 = ( vtx0->x >= tx ) ;
	    /* check if endpoints are on same side of the Y axis (i.e. X's
	     * are the same); if so, it's easy to test if edge hits or misses.
	     */
	    if ( xflag0 == ( vtx1->x >= tx ) ) {

		/* if edge's X values both right of the point, must hit */
		if ( xflag0 ) inside_flag = !inside_flag ;

		} else {
		/* compute intersection of pgon segment with +X ray, note
		 * if >= point's X; if so, the ray hits it.
		 */
		if ( (vtx1->x - (vtx1->y-ty)*
		     ( vtx0->x-vtx1->x)/(vtx0->y-vtx1->y)) >= tx ) {
		    inside_flag = !inside_flag ;
		}
	    }
	}

	/* move to next pair of vertices, retaining info as possible */
	yflag0 = yflag1 ;
	vtx0 = vtx1 ;
	vtx1 ++ ;
    }

    return( inside_flag ) ;
}


#else

// Code from http://tog.acm.org/GraphicsGems//gemsiv/ptpoly_haines/ptinpoly.c
bool PolygonPrimitive::isPointInside( Point3d& point ) {
	
	bool yFlag0, yFlag1, insideFlag ;

	int size = points.size();
	Point3d* currPoint = &points[size-1];
    /* get test bit for above/below X axis */
    yFlag0 = ( currPoint->y >= point.y ) ;
    Point3d* nextPoint = &points[0];

    insideFlag = false ;
    for ( int j = size+1 ; --j ; ) {

		yFlag1 = ( nextPoint->y >= point.y ) ;
		/* Check if endpoints straddle (are on opposite sides) of X axis
		 * (i.e. the Y's differ); if so, +X ray could intersect this edge.
		 * The old test also checked whether the endpoints are both to the
		 * right or to the left of the test point.  However, given the faster
		 * intersection point computation used below, this test was found to
		 * be a break-even proposition for most polygons and a loser for
		 * triangles (where 50% or more of the edges which survive this test
		 * will cross quadrants and so have to have the X intersection computed
		 * anyway).  I credit Joseph Samosky with inspiring me to try dropping
		 * the "both left or both right" part of my code.
		 */
		if ( yFlag0 != yFlag1 ) {
			/* Check intersection of pgon segment with +X ray.
			 * Note if >= point's X; if so, the ray hits it.
			 * The division operation is avoided for the ">=" test by checking
			 * the sign of the first vertex wrto the test point; idea inspired
			 * by Joseph Samosky's and Mark Haigh-Hutchinson's different
			 * polygon inclusion tests.
			 */
			if ( ((nextPoint->y-point.y) * (currPoint->x-nextPoint->x) >=
				 (nextPoint->x-point.x) * (currPoint->y-nextPoint->y)) == yFlag1 ) {
				insideFlag = !insideFlag ;
			}
		}

		/* Move to the next pair of vertices, retaining info as possible. */
		yFlag0 = yFlag1 ;
		currPoint = nextPoint ;
		nextPoint ++;
    }

    return( insideFlag ) ;
}
#endif


PolygonPrimitive* PolygonPrimitive::intersectWith( PolygonPrimitive* toIntersect ) {

	PolygonPrimitive* current = this;
	PolygonPrimitive* other = toIntersect;

	int nextIndex = 0;
	PolygonPrimitive* result = new PolygonPrimitive();

	if( other->isPointInside( points[0] ) ) {
		result->points.push_back( points[0] );
		nextIndex = 1;
	}
	else if( isPointInside( other->points[0] ) ) {
		result->points.push_back( other->points[0] );
		current = toIntersect;
		other = this;
		nextIndex = 1;
	}

	int indexOfSegmentToIgnore = -1;
	Point3d intersectionPoint;

	int maxCount = other->nbPoints() + nbPoints();
	int count = 0;

	while( count < maxCount ) {
		int intersectionIndex;		
		if( result->points.empty() ) {
			intersectionIndex = other->intersectWithSegment( points[nextIndex], points[(nextIndex+1)%nbPoints()], intersectionPoint );
			if( intersectionIndex >= 0 ) {
				result->points.push_back( intersectionPoint );
				indexOfSegmentToIgnore = intersectionIndex;
			}
			nextIndex = (nextIndex + 1)%nbPoints();
			if( nextIndex == 0 )
				break;
		} 
		else {
			intersectionIndex = other->intersectWithSegment( 
				result->points.back(), current->points[nextIndex], intersectionPoint, indexOfSegmentToIgnore );

			Point3d* pointToAdd;

			if( intersectionIndex < 0 ) {
				// No interesection
				pointToAdd = &current->points[nextIndex];
				nextIndex = (nextIndex + 1)%current->nbPoints();
				indexOfSegmentToIgnore = -1;
			}
			else {
				// Intersection
				indexOfSegmentToIgnore = (nextIndex + current->nbPoints() - 1)%current->nbPoints();
				pointToAdd = &intersectionPoint;
				PolygonPrimitive* temp = other;
				other = current;
				current = temp;
				nextIndex = (intersectionIndex + 1)%current->nbPoints();
			}

			// Check if we went around
			if( (result->points[0] - *pointToAdd).length() < 0.00001 )
				break;
			result->points.push_back( *pointToAdd );
		}
		count++;
	}

	if( count == maxCount )
		logPrint( "Error while intersecting polygon primitives.\n" );

	return result;

}

void PolygonPrimitive::toMesh( const char* filename ) {

	// Subtracting ears method
	// See: http://en.wikipedia.org/wiki/Polygon_triangulation

	FILE* f = fopen( filename, "w" );

	fprintf( f, "o 1\n\n" );

	DynamicArray<int> originalIndices;

	int size = points.size();
	for( int i=0; i<size; ++i ) {
		originalIndices.push_back(i);
		fprintf( f, "v %lf %lf %lf\n", points[i].z, points[i].y, points[i].x );
	}

	fprintf( f, "\n" );
	fprintf( f, "usemtl Default\n" );

	// Build the ear in there
	PolygonPrimitive triangle;

	while( originalIndices.size() > 2 ) {
		size = originalIndices.size();

		for( int i=0; i<size; ++i ) {
			int j = (i+1)%size;
			int k = (i+2)%size;
		
			triangle.clear();
			triangle.addPoint( points[ originalIndices[i] ] );
			triangle.addPoint( points[ originalIndices[j] ] );
			triangle.addPoint( points[ originalIndices[k] ] );


			// Check that its an ear:
			//   1) it is CCW
			//   2) no points are in triangle ijk
			if( triangle.volume() < 0 )
				continue;
			int index;
			for( index=0; index<size; ++index ) {
				if( index == i || index == j || index == k )
					continue;
				if( triangle.isPointInside( points[ originalIndices[index] ] ) )
					break;
			}
			if( index == size ) {
				fprintf( f, "f %d %d %d\n", originalIndices[i]+1, originalIndices[j]+1, originalIndices[k]+1 );

				// Remove the ear (the middle vertex)
				originalIndices.erase( originalIndices.begin() + j );

				break;
			}
		}
	
	}

	fclose( f );

}

PolygonPrimitive* PolygonPrimitive::cleanSelfIntersection( int startingIndex ) {

	// Starting index ignored for now!
	int size = points.size();

	DynamicArray<Point3d> result;
	result.push_back( points[0] );
	Point3d intersection;

	for( int i=0; i<size-1; ++i) {
		bool intersectionFound = false;
		for( int j=size-1; j>i; --j ) {
			if( PointPrimitive::intersectSegments( points[i], points[i+1], points[j], points[(j+1)%size], intersection ) ) {
				intersectionFound = true;
				result.push_back(intersection);
				i = j-1;
				break;
			}
		}
		if( !intersectionFound )
			result.push_back( points[i+1] );
	}

	points.clear();
	points.insert( points.begin(), result.begin(), result.end() );

	return this;
}

int PolygonPrimitive::intersectWithSegment( Point3d& segmentStart, Point3d& segmentEnd, Point3d& intersection, int indexOfSegmentToIgnore ) {

	int size = points.size();
	int result = -1;
	double resultDist = 0;
	Point3d tempIntersection;
	for( int i=0; i<size; ++i ) {
		if( i == indexOfSegmentToIgnore ) 
			continue;

		if( PointPrimitive::intersectSegments( segmentStart, segmentEnd, points[i], points[(i+1)%size], tempIntersection ) ) {
			double newDist = (tempIntersection - segmentStart).length();
			if( result < 0 || newDist < resultDist ) {
				intersection = tempIntersection;
				result = i;
				resultDist = newDist;
			}
		}
	}

	return result;
}


Primitive* CurvePrimitive::closeOrCopy( double threshold ) {
	
	bool close = true;
	if( points.size() < 2 )
		close = false;
	else {
		Vector3d vec = points.front() - points.back();
		if( vec.length() > threshold )
			close = false;
	}

	PointPrimitive* result = NULL;
	if( close ) {
		result = new PolygonPrimitive();
	}
	else {
		result = new CurvePrimitive();
	}

	int size = points.size();
	for( int i=0; i<size; ++i ) {
		result->addPoint( points[i] );
	}

	if( close ) {
		((PolygonPrimitive *)result)->cleanSelfIntersection();
		((PolygonPrimitive *)result)->makeCCW();
	}

	return result;
}


PolygonPrimitive* CurvePrimitive::makeVolumetric( double thickness ) {
	PolygonPrimitive* result = new PolygonPrimitive();

	int size = points.size();
	if( size == 0 )
		return result;


	if( size == 1 ) {
		// Make a simple triangle around the point
		double temp = sqrt(3.0) / 2.0; // sin(120)
		result->addPoint( points[0] + Vector3d( 0, 1, 0 ) * thickness );
		result->addPoint( points[0] + Vector3d( -temp, -0.5, 0 ) * thickness );
		result->addPoint( points[0] + Vector3d(  temp, -0.5, 0 ) * thickness );

		result->makeCCW();
		return result;
	}

	for( int i=0; i<size; ++i ) {
		const Point3d& prevPoint = (i==0)?points[0]:points[i-1];
		const Point3d& currPoint = points[i];
		const Point3d& nextPoint = (i==size-1)?points[size-1]:points[i+1];

		Vector3d offsetVec(	nextPoint.y-prevPoint.y, prevPoint.x-nextPoint.x );
		offsetVec = offsetVec.unit();
		offsetVec *= thickness;
		result->insertPoint( i, currPoint + offsetVec );
		result->insertPoint( i, currPoint - offsetVec );
	}

	result->cleanSelfIntersection();
	result->makeCCW();
	return result;

}

void CurvePrimitive::collisionVolume( FILE *f, double thickness ) {

	int size = points.size();
	if( size < 2 ) 
		return;

	double dist = 3 * thickness;

	for( int i=0; i<size; ++i ) {
		Vector3d edge = points[(i+1)%size] - points[i];
		if( dist > 2*thickness ) {
			fprintf( f, "   CDP_Sphere %lf %lf %lf %lf\n", points[i].z, points[i].y, points[i].x, thickness );			
			dist = 0;
		}
		dist += edge.length();
	}
}

void PolygonPrimitive::collisionVolume( FILE *f, double thickness ) {

	int size = points.size();
	if( size < 2 ) 
		return;

	double dist = 3 * thickness;

	for( int i=0; i<size; ++i ) {
		Vector3d edge = points[(i+1)%size] - points[i];
		double len = edge.length();
		if( len == 0 ) 
			continue;
		if( dist > 2*thickness ) {
		
			Vector3d normal( -edge.y, edge.x, edge.z );
			normal = normal / len;
			Point3d center = points[i] + (normal * thickness);
			fprintf( f, "   CDP_Sphere %lf %lf %lf %lf\n", center.z, center.y, center.x, thickness );
			
			dist = 0;
		}
		dist += len;
	}
}

void PolygonPrimitive::logDump() {
	int size = points.size();

	logPrint( "PolygonPrimitive* prim = new PolygonPrimitive();\n" );
	for( int i=0; i<size; ++i ) {
		logPrint( "prim->addPoint( Point3d(%lf, %lf, %lf) );\n", points[i].x, points[i].y, points[i].z); 
	}
	logPrint( "\n\n" );
}
