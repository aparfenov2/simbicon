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

#include ".\spherecdp.h"
#include <GLUtils/GLUtils.h>
#include <Physics/CapsuleCDP.h>
#include <Physics/PlaneCDP.h>
#include <Physics/RigidBody.h>

SphereCDP::SphereCDP(RigidBody* theBdy, Point3d& c_, double r_) : CollisionDetectionPrimitive(theBdy){
	s.pos = c_;
	s.radius = r_;
	type = SPHERE_CDP;
}

SphereCDP::~SphereCDP(void){
}


/**
	Draw an outline of the sphere
*/
void SphereCDP::draw(){
	GLUtils::drawSphere(s.pos, s.radius, 5);
}

/**
	updates the world sphere.
*/
void SphereCDP::updateToWorldPrimitive(){
	wS.pos = bdy->getWorldCoordinates(s.pos);
	wS.radius = s.radius;
}

