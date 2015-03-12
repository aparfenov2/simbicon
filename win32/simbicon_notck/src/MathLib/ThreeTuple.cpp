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

#include "ThreeTuple.h"

/*constructors*/
ThreeTuple::ThreeTuple(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

ThreeTuple::ThreeTuple(double x,double y){
	this->x = x;
	this->y = y;
	this->z = 0;
}

ThreeTuple::ThreeTuple(ThreeTuple& p){
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

ThreeTuple::ThreeTuple(double* values){
	this->x = values[0];
	this->y = values[1];
	this->z = values[2];
}

ThreeTuple::ThreeTuple(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

/*destructor*/
ThreeTuple::~ThreeTuple(){
}

/**
	creates an exact copy of the current threetuple and returns a pointer to it.
*/
/*
ThreeTuple* ThreeTuple::createCopy(){
	return new ThreeTuple(this->x, this->y, this->z);
}
*/
