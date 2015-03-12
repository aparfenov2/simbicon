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

#include <MathLib/Point3d.h>
#include <MathLib/Vector3d.h>
#include <MathLib/Quaternion.h>

/*======================================================================================================================================================================*
 * This class acts as a container for the state information (position, orientation, velocity and angular velocity - all of them stored in world coordinates, about the  *
 * center of mass) of a rigid body.                                                                                                                                     *
 *======================================================================================================================================================================*/

class RBState{
public:
	//NOTE: all the quantities here are in world coordinates

	// the position of the center of mass of the rigid body
	Point3d position;
	// its orientation
	Quaternion orientation;
	// the velocity of the center of mass
	Vector3d velocity;
	// and finally, the angular velocity about the center of mass
	Vector3d angularVelocity;
	
public:
	/**
		Default constructor - populate the data members using safe values..
	*/
	RBState(void);

	/**
		A copy constructor.
	*/
	RBState(const RBState& other);

	/**
		and a copy operator	
	*/
	RBState& operator = (const RBState& other);
	/**
		Default destructor.
	*/
	~RBState(void);
};
