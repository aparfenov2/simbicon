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

#include ".\rbstate.h"

/**
	Default constructor - populate the data members using safe values..
*/
RBState::RBState(void){
	//guess some default values if this constructor is used...
	this->position = Point3d(0,0,0);
	this->orientation = Quaternion(1,Vector3d(0,0,0));
	this->velocity = Vector3d(0,0,0);
	this->angularVelocity = Vector3d(0,0,0);
}

/**
	A copy constructor.
*/
RBState::RBState(const RBState& other){
	this->position = other.position;
	this->orientation = other.orientation;
	this->velocity = other.velocity;
	this->angularVelocity = other.angularVelocity;
}

/**
	and a copy operator	
*/
RBState& RBState::operator = (const RBState& other){
	this->position = other.position;
	this->orientation = other.orientation;
	this->velocity = other.velocity;
	this->angularVelocity = other.angularVelocity;
	return *this;
}

RBState::~RBState(void){
		
}

