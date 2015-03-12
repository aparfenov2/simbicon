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

#include <Utils/Utils.h>
#include <MathLib/TransformationMatrix.h>

/*========================================================================================================================================================================*
 * This class implements an interface for collision detection primitives such as spheres, capsules and so on.                                                             *
 *========================================================================================================================================================================*/

class SphereCDP;
class CapsuleCDP;
class PlaneCDP;
class RigidBody;
class BoxCDP;

#define UNKNOWN_CDP 0
#define SPHERE_CDP 1
#define CAPSULE_CDP 2
#define PLANE_CDP 3
#define BOX_CDP 4



class CollisionDetectionPrimitive{
protected:
	//keep track of the rigid body that this collision detection primitive belongs to - useful to update world coordinates, etc
	RigidBody* bdy;
	int type;

public:
	CollisionDetectionPrimitive(RigidBody* theBody);
	virtual ~CollisionDetectionPrimitive(void);

	virtual void updateToWorldPrimitive() = 0;

	/**
		draw an outline of the primitive...
	*/
	virtual void draw();

	/**
		returns the type of this collision detection primitive.
	*/
	inline int getType(){return type;}

};

