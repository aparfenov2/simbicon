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

#include ".\planecdp.h"
#include <Physics/SphereCDP.h>
#include <Physics/CapsuleCDP.h>
#include <Physics/RigidBody.h>

PlaneCDP::PlaneCDP(RigidBody* theBody, Vector3d n_, Point3d o_) : CollisionDetectionPrimitive(theBody){
	//make sure we have a unit vector;
	p.n = n_;
	p.n.toUnit();
	p.p = o_;

	type = PLANE_CDP;
}

PlaneCDP::~PlaneCDP(void){
}

	
/**
	Draw an outline of the capsule
*/
void PlaneCDP::draw(){
	//we won't draw the plane...
}


void PlaneCDP::updateToWorldPrimitive(){
//	bdy->state.orientation.fastRotate(p.n, &wP.n);
	wP.n = bdy->getWorldCoordinates(p.n);
	wP.p = bdy->getWorldCoordinates(p.p);
}

