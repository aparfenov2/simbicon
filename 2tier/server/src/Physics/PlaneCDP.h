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
#include <Utils/Utils.h>
#include <MathLib/Plane.h>
#include <Physics/CollisionDetectionPrimitive.h>


/*========================================================================================================================================================================*
 * This class implements a plane class that will be used as a collision detection primitive.                                                                              *
 * A plane is represented by the position of one point on the plane, as well as the normal (unit vector) to the plane. We will store these two quantities both in local   *
 * coordinates, and in world coordinates which will be used for the collision detection. NOTE: we will not be evaluating the collision between different planes because   *
 * I will assume that they are all part of fixed objects only.
 *========================================================================================================================================================================*/
class PlaneCDP : public CollisionDetectionPrimitive{
private:
	//this is the plane, expressed in the local coordinates of the rigid body that owns it
	Plane p;
	//and this is the plane expressed in world coordinates
	Plane wP;
	
public:
	PlaneCDP(RigidBody* theBody, Vector3d n_, Point3d o_);
	~PlaneCDP(void);

	virtual void updateToWorldPrimitive();

	virtual void draw();
	Vector3d getNormal(){return p.n;}
	Point3d getPointOnPlane(){return p.p;};

};


