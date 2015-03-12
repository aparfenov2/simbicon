/*
	Simbicon 1.5 Controller Editor Framework, 
	Copyright 2009 Stelian Coros, Philippe Beaudoin and Michiel van de Panne.
	All rights reserved. Web: www.cs.ubc.ca/~van/simbicon_cef

	This file is part of the Simbicon 1.5 Controller Editor Framework.

	Simbicon 1.5 Controller Editor Framework is free software: you can 
	redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Simbicon 1.5 Controller Editor Framework is distributed in the hope 
	that it will be useful, but WITHOUT ANY WARRANTY; without even the 
	implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Simbicon 1.5 Controller Editor Framework. 
	If not, see <http://www.gnu.org/licenses/>.
*/

#include <MathLib/Point3d.h>
#include <Include/glHeaders.h>
#include <MathLib/Vector3d.h>
/**
	draws this point.
*/
void Point3d::drawObject(){
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3d(this->x, this->y, this->z);
	glEnd();
	glPointSize(1);
}

/**
	addition of two vectors - results in a new vector.
*/
Point3d Point3d::operator + (const Vector3d &v) const{
	return Point3d(this->x + v.x, this->y + v.y,this->z + v.z);
}


/**
	add this vector to the current point
*/
Point3d& Point3d::operator += (const Vector3d &v){
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}


/**
	difference between two points - results in a new vector.
*/
Vector3d Point3d::operator - (const Point3d &p) const{
	return Vector3d(this->x - p.x, this->y - p.y,this->z - p.z);
}

	//*this = p + v * s
void Point3d::setToOffsetFromPoint(const Point3d &p, const Vector3d& v, double s){
	this->x = p.x + v.x*s;
	this->y = p.y + v.y*s;
	this->z = p.z + v.z*s;
}

