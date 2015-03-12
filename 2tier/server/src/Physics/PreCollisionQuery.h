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

#include <Physics/RigidBody.h>
#include <Utils/Utils.h>


/**
 *	This class provides an interface for classes that need to interact with a physics simulator, in order to control its behaviour. The methods here 
 *  will be called by the simulator at certain points (for instance, when determining if collisions need to be performed between two arbitrary objects). 
 *  It is up to the class that implements this interface to handle each method accordingly. 
 */
class PreCollisionQuery{
protected:
	
public:
	PreCollisionQuery(void);
	virtual ~PreCollisionQuery(void);

	/**
		This method returns true if the pair of rigid bodies here should be checked for collisions, false otherwise.
		Note that the ground does not have a rigid body associated with it, so if a rigid body is NULL, it means it
		corresponds to the ground. The joined variable is set to true if the two bodies are connected by a joint,
		false otherwise.
	*/
	virtual bool shouldCheckForCollisions(RigidBody* rb1, RigidBody* rb2, bool joined);

};
