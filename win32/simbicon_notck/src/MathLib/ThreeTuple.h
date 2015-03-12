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

#include <MathLib/mathLib.h>
#include <stdio.h>


class ThreeTuple  {
//these variables are declared public because they provide faster access
public:
	double x;
	double y;
	double z;

public:
	/**
		some useful constructors 
	*/
	ThreeTuple();
	ThreeTuple(ThreeTuple&);
	ThreeTuple(double x, double y, double z);
	ThreeTuple(double x, double y);
	ThreeTuple(double*);
	~ThreeTuple();

	/**
		setters and getters
	*/
	inline double getX() const{
		return this->x;
	}
	inline double getY() const{
		return this->y;
	}
	inline double getZ() const{
		return this->z;
	}

	inline void setX(double x){
		this->x = x;
	}
	inline void setY(double y){
		this->y = y;
	}
	inline void setZ(double z){
		this->z = z;
	}

	inline void setValues(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void setValues(ThreeTuple& p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}

	/**
		this is an equality operator.
	*/
	inline bool operator == (const ThreeTuple& p) const{
		double dx = this->x-p.x;
		double dy = this->y-p.y;
		double dz = this->z-p.z;
		return (ZERO_WITHIN_EPSILON(dx) && ZERO_WITHIN_EPSILON(dy) && ZERO_WITHIN_EPSILON(dz));
	}

	/**
		this is an equality operator.
	*/
	inline bool operator != (const ThreeTuple& p) const{
		return !(*this == p);
	}
	/**
		This method is used for debugging purposes. It prints the x, y and z components.
	*/
	inline void print(){
		printf("(%lf, %lf, %lf)\n", x, y, z);
	}


	/**
		and a copy operator.
	*/
	inline ThreeTuple& operator = (ThreeTuple& p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
		return *this;
	}
	/**
		creates an exact copy of the current threetuple and returns a pointer to it.
	*/
//	virtual ThreeTuple* createCopy();
};

