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

#include <Physics/CollisionDetectionPrimitive.h>
#include <MathLib/Point3d.h>
#include <MathLib/TransformationMatrix.h>
#include <Utils/Utils.h>
#include <MathLib/Capsule.h>

/*========================================================================================================================================================================*
 * This class implements a capsule class that will be used as a collision detection primitive.                                                                            *
 * A capsule is represented by the position of the two end points and the radius length. We will also store a temp position for the world coordinates of the endppoints   * 
 * of the capsule. This will be used when evaluating the contact points with other primitives, and it needs to be updated any time the world position of the object that  *                      
 * owns this capsule changes.                                                                                                                                             *
 *========================================================================================================================================================================*/
class CapsuleCDP : public CollisionDetectionPrimitive{
private:
	//a capsule is really just an infinite number of spheres that have the center along a segment. Therefore, to define the capsule we need the
	//two end points and the radius
	Capsule c;
	Capsule wC;
public:
	CapsuleCDP(RigidBody* theBody, Point3d& a_, Point3d& b_, double r_);
	~CapsuleCDP(void);

	virtual void updateToWorldPrimitive();

	/**
		Draw an outline of the capsule
	*/
	virtual void draw();

	/**
		return the radius of the sphere
	*/
	inline double getRadius(){
		return this->c.radius;
	}

	/**
		return the position of the first endpoint.
	*/
	inline Point3d getA(){
		return c.p1;
	}

	/**
		return the position of the first endpoint.
	*/
	inline Point3d getB(){
		return c.p2;
	}

};
