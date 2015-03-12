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

#pragma once

#include <MathLib\ThreeTuple.h>
#include <Utils/Utils.h>


class Vector3d;
/*=====================================================================================================================================================*
 | This class implements a Point in 3d. It will be stored in homogenous coordinates (x, y, z, w). Every time a w-component is set, the x, y, z will be |
 | rescaled so that w results in being 1 - in other words, the w component is always 1. The x, y and z components are inherited from the Three Tuple   |
 | class that this class extends.                                                                                                                      |
 *=====================================================================================================================================================*/

class Point3d : public ThreeTuple{
public:
	/**
		some useful constructors.
	*/
	Point3d() : ThreeTuple(){
	}
	Point3d(double x, double y, double z) : ThreeTuple(x, y, z){
	}

	Point3d(double x, double y, double z, double w) : ThreeTuple(x, y, z){
		setW(w);
	}

	Point3d(double x, double y) : ThreeTuple(x, y){
	}

	Point3d(ThreeTuple &p) : ThreeTuple(p){
	}

	Point3d(const Point3d& other){
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	Point3d& operator = (const Point3d& other){
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	/**
		default destructor.
	*/
	~Point3d(){}
	
	/**
		this method is used to set the w component.
	*/
	inline void setW(double w){
		if (w == 0)
			throwError("Cannot set w-component of a point to 0.");
		this->x/=w;
		this->y/=w;
		this->z/=w;
	}

	//*this = p + v * s
	void setToOffsetFromPoint(const Point3d &p, const Vector3d& v, double s);

	/**
		addition of a point and a vector - results in a point
	*/
	Point3d operator + (const Vector3d &v) const;

	/**
		add this vector to the current point
	*/
	Point3d& operator += (const Vector3d &v);

	inline Point3d& operator /= (double val){
		double v = 1/val;
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	/**
		difference betewwn two points - results in a vector
	*/
	Vector3d operator - (const Point3d &p) const;

	/**
		Returns a vector that has all its components multiplied by -1.
	*/
	inline Point3d operator - (){
		return Point3d(-this->x, -this->y, -this->z);
	}

	void drawObject();

//	virtual Point3d* createCopy();
};


