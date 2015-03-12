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
#include <MathLib/Sphere.h>
#include <MathLib/TransformationMatrix.h>
#include <Utils/Utils.h>

/*========================================================================================================================================================================*
 * This class implements a sphere class that will be used as a collision detection primitive.                                                                             *
 * A sphere is represented by the position of the center and the radius length. We will also store a temp position for the world coordinates of the center of the sphere. *
 * This will be used when evaluating the contact points with other primitives, and it will be automatically 
 *========================================================================================================================================================================*/
class SphereCDP : public CollisionDetectionPrimitive{
public:
	//keep track of the local-coordinates sphere used by this collision detection primitive
	Sphere s;
	//and this is the sphere, expressed in world coordinates
	Sphere wS;
public:
	SphereCDP(RigidBody* theBdy, Point3d& c_, double r_);
	virtual ~SphereCDP(void);

	virtual void updateToWorldPrimitive();

	/**
		Draw an outline of the sphere
	*/
	virtual void draw();

	/**
		return the radius of the sphere
	*/
	inline double getRadius(){
		return s.radius;
	}

	/**
		return the center of the sphere, expressed in local coordinates
	*/
	inline Point3d getCenter(){
		return s.pos;
	}

};
