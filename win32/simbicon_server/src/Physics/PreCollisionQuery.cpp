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

#include <Physics/PreCollisionQuery.h>

PreCollisionQuery::PreCollisionQuery(void){

}


PreCollisionQuery::~PreCollisionQuery(void){

}

/**
	This method returns true if the pair of rigid bodies here should be checked for collisions, false otherwise.
	Note that the ground does not have a rigid body associated with it, so if a rigid body is NULL, it means it
	corresponds to the ground. The joined variable is set to true if the two bodies are connected by a joint,
	false otherwise.
*/
bool PreCollisionQuery::shouldCheckForCollisions(RigidBody* rb1, RigidBody* rb2, bool joined){
	//we do not want to check the objects for collisions if they are connected by a joint (joint limits should be used for that).
	if (joined == true)
		return false;

	//don't allow collisions between static things
	if (rb1->isLocked() && rb2->isLocked())
		return false;

	if (rb1->getAFParent() != NULL)
		if (rb1->getAFParent() == rb2->getAFParent())
			return false;
	return true;
}

