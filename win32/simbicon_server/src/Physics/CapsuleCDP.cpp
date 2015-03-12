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

#include ".\capsulecdp.h"
#include <GLUtils/GLUtils.h>
#include <Physics/SphereCDP.h>
#include <Physics/PlaneCDP.h>
#include <Physics/RigidBody.h>

CapsuleCDP::CapsuleCDP(RigidBody* theBody, Point3d& a_, Point3d& b_, double r_) : CollisionDetectionPrimitive(theBody){
	this->c.p1 = a_;
	this->c.p2 = b_;
	this->c.radius = r_;
	type = CAPSULE_CDP;
}

CapsuleCDP::~CapsuleCDP(void){
}


/**
	draw an outline of the capsule
*/

void CapsuleCDP::draw(){
	GLUtils::drawCylinder(this->c.radius, Vector3d(this->c.p1, this->c.p2), this->c.p1, 6);
	GLUtils::drawSphere(this->c.p1, this->c.radius, 5);
	GLUtils::drawSphere(this->c.p2, this->c.radius, 5);
}

void CapsuleCDP::updateToWorldPrimitive(){
	wC.p1 = bdy->getWorldCoordinates(c.p1);
	wC.p2 = bdy->getWorldCoordinates(c.p2);
	wC.radius = c.radius;
}

