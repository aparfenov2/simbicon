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

#include <Physics/AbstractRBEngine.h>
#include <ode/ode.h>
//#include <ode/joint.h>
#include <Physics/CollisionDetectionPrimitive.h>
#include <Physics/SphereCDP.h>
#include <Physics/CapsuleCDP.h>
#include <Physics/BoxCDP.h>
#include <Physics/PlaneCDP.h>
#include <Physics/PreCollisionQuery.h>



/*-------------------------------------------------------------------------------------------------------------------------------------------------*
 * This class is used as a wrapper that is designed to work with the Open Dynamics Engine. It uses all the rigid bodies (together with the joints) *
 * that are loaded with RBCollection, and has methods that link with ODE to simulate the physics. If a different physics engine is to be used,     *
 * then ideally only the methods of this class need to be re-implemented, and the rest of the application can stay the same.                       *
 *-------------------------------------------------------------------------------------------------------------------------------------------------*/
class ODEWorldFactory {

public:
	static AbstractRBEngine * createODEWorld();

};
