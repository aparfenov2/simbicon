#pragma once

#include <MathLib/Point3d.h>
#include <MathLib/Vector3d.h>
#include <Include/glHeaders.h>

#include <GLUtils/GLMesh.h>

class PolygonPrimitive;

class Primitive {

protected:
	Vector3d color;

public:
	Primitive() : color(1,1,1) {}

	void setColor( double r, double g, double b ) {
		color.x = r;
		color.y = g;
		color.z = b;
	}

	virtual void draw() = 0;

	virtual void centerOnPoint( const Point3d& center ) = 0;

	virtual PolygonPrimitive* makeVolumetric( double thickness ) = 0;

	virtual void collisionVolume( FILE* f, double thickness ) = 0;
};


class PointPrimitive : public Primitive {

protected:	
	DynamicArray<Point3d> points;

public:

	PointPrimitive() {}

	PointPrimitive( const PointPrimitive& other )
	{	
		int size = other.points.size();
		for( int i = 0; i<size; ++i )
			points.push_back( other.points[i] );
	}

	~PointPrimitive() {
		clear();
	}
	
	int nbPoints() {
		return points.size();
	}

	void clear() {
		points.clear();
	}

	void addPoint( const Point3d& newPoint ) {
		points.push_back( newPoint );
	}

	void insertPoint( int i, const Point3d& newPoint ) {
		points.insert( points.begin()+i, newPoint );
	}

	static bool intersectSegments( Point3d& start1, Point3d& end1, Point3d& start2, Point3d& end2, Point3d& intersection );

	void centerOnPoint( const Point3d& center ) {
	
		int size = points.size();
		for( int i = 0; i<size; ++i )
			points[i] = points[i] - center;

	
	}


};

class PolygonPrimitive : public PointPrimitive {

public:

	PolygonPrimitive() {}

	PolygonPrimitive( const PolygonPrimitive& other ) :
		PointPrimitive( other )
	{	
	}

	void draw() {
	
		if( points.size() < 2 ) return;
		glColor3d( color.x, color.y, color.z );	
		glBegin(GL_LINE_LOOP);

			int size = points.size();
			for( int i=0; i<size; ++i ) {
				glVertex2d( points[i].x, points[i].y );
			}
		glEnd();

	}

	// Make sure the vertices are listed in CCW order
	void makeCCW();

	PolygonPrimitive* makeVolumetric( double thickness ) {
		return new PolygonPrimitive(*this);
	}

	// Compute signed volume (CW < 0, CCW > 0)
	double volume();

	Point3d midPoint();

	bool isPointInside( Point3d& point );

	// Cleans self. Return a pointer to self.
	PolygonPrimitive*  cleanSelfIntersection( int startingIndex = -1 );

	PolygonPrimitive* intersectWith( PolygonPrimitive* toIntersect );

	// Convert to an obj file
	void toMesh( const char* filename );


	// Return the index of the first point of the segment of this polygon that intersects the passed segment, -1 if none
	int intersectWithSegment( Point3d& segmentStart, Point3d& segmentEnd, Point3d& intersection, int indexOfSegmentToIgnore = -1 );


	void logDump();

	void collisionVolume( FILE* f, double thickness );

};

class CurvePrimitive : public PointPrimitive {

public:


	CurvePrimitive() {}

	CurvePrimitive( const CurvePrimitive& other ) :
		PointPrimitive( other )
	{	
	}

	void draw() {
	
		if( points.size() < 2 ) return;
		glColor3d( color.x, color.y, color.z );	
		glBegin(GL_LINE_STRIP);

			int size = points.size();
			for( int i=0; i<size; ++i ) {
				glVertex2d( points[i].x, points[i].y );
			}

		glEnd();

	}

	/**
		Creates a new primitive either by cloning this one
		or by closing it if the ending point is close enough to the starting point
	*/
	Primitive* closeOrCopy( double threshold );

	PolygonPrimitive* makeVolumetric( double thickness );

	void collisionVolume( FILE* f, double thickness );

};