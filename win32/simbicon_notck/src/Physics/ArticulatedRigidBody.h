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

/*=======================================================================================================================================================================*
 * We will treat the articulated rigid bodies as normal rigid bodies that are connected by joints. The joints are needed to enforce constraints between the articulated  *
 * rigid bodies, but other than that, the dynamics are the same as for rigid bodies. We will assume that every articulated figure will be loop-free (tree hierarchies).  *
 *=======================================================================================================================================================================*/
class Joint;
class ArticulatedRigidBody : public RigidBody{
friend class Joint;
friend class ArticulatedFigure;
friend class SimBiController;
private:
	//this is the parent joint.
	Joint* pJoint;
	//and these are the child joints - it can have as many as it wants.
	DynamicArray<Joint*> cJoints;
	//this is the articulated figure that the rigid body belongs to
	ArticulatedFigure* AFParent;
public:
	/**
		Default constructor
	*/
	ArticulatedRigidBody(void);

	/**
		This method draws the current rigid body.
	*/
	virtual void draw(int flags);

	/**
		Default destructor
	*/
	virtual ~ArticulatedRigidBody(void);

	/**
		returns the parent joint for the current articulated body
	*/
	inline Joint* getParentJoint(){return pJoint;};

	/**
		this method always returns true
	*/
	virtual bool isArticulated(){
		return true;
	}


	virtual ArticulatedFigure* getAFParent(){
		return AFParent;
	}

};
