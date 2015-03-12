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

#include <Physics/ArticulatedRigidBody.h>
#include <Physics/UniversalJoint.h>
#include <Physics/HingeJoint.h>
#include <Physics/BallInSocketJoint.h>

/*======================================================================================================================================================================*
 * An articulated figure is composed of many articulated rigid bodies that are interconnected by joints. Characters, cars, ropes, etc, can all be viewed as articulated *
 * figures. One note is that we will only allow tree structures - no loops.                                                                                             *
 *======================================================================================================================================================================*/
class RBCollection;
class ArticulatedFigure  {
friend class Character;
friend class ODEWorld;
protected:
	//we will keep track of the root of the articulated figure. Based on the outgoing joints we can access its, children, and so on
	ArticulatedRigidBody* root;

	//this is the name of the articulated figure
	char name[100];
	double mass;
public:
	/**
		Default constructor
	*/
	ArticulatedFigure(void);

	/**
		Default destructor
	*/
	~ArticulatedFigure(void);


	/**
		This method is used to automatically fix the errors in the joints (i.e. drift errors caused by numercial integration). At some future
		point it can be changed into a proper stabilization technique.
	*/
	void fixJointConstraints(bool fixOrientations = true, bool fixVelocities = false);

	/**
		This method is used to get all the joints in the articulated figure and add them to the list of joints that is passed in as a paramter.
	*/
	void addJointsToList(DynamicArray<Joint*> *joints);

	/**
		This method is used to compute the total mass of the articulated figure.
	*/
	void computeMass();

	/**
		This method is used to get the total mass of the articulated figure.
	*/
	double getMass();

	/**
		This method is used to load the details of an articulated figure from file. The PhysicalWorld parameter points to the world in which the objects
		that need to be linked live in.
	*/
	void loadFromFile(FILE* fp, AbstractRBEngine* world);
	
};
