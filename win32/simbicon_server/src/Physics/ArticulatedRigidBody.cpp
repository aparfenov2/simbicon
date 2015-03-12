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

#include "articulatedrigidbody.h"
#include <Physics/Joint.h>


ArticulatedRigidBody::ArticulatedRigidBody(void){
	this->pJoint = NULL;
	this->AFParent = NULL;
}

ArticulatedRigidBody::~ArticulatedRigidBody(void){
	//delete all the child joints
	for (uint i=0;i<cJoints.size();i++)
		delete cJoints[i];
}

/**
	This method draws the current rigid body.
*/
void ArticulatedRigidBody::draw(int flags){
	RigidBody::draw(flags);
	
	if (!pJoint)
		return;

	if (flags & SHOW_JOINTS){
		//we will draw a little sphere at the location of the joint (we'll do it twice - once for the parent and one for the child. They should coincide
		//if the joint constraint is properly satisfied
		GLUtils::drawSphere(this->getWorldCoordinates(pJoint->cJPos), 0.02, 4);
		GLUtils::drawSphere(pJoint->parent->getWorldCoordinates(pJoint->pJPos), 0.02, 4);
	}
}

