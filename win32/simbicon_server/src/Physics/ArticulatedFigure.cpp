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

#include ".\articulatedfigure.h"
#include <Physics/AbstractRBEngine.h>
#include <Physics/RBUtils.h>
#include <Utils/Utils.h>
/**
	Default constructor
*/
ArticulatedFigure::ArticulatedFigure(void){
	root = NULL;
	name[0] = '\0';
	mass = 0;
}

ArticulatedFigure::~ArticulatedFigure(void){
}

/**
	This method is used to automatically fix the errors in the joints (i.e. drift errors caused by numercial integration). At some future
	point it can be changed into a proper stabilization technique.
*/
void ArticulatedFigure::fixJointConstraints(bool fixOrientations, bool fixVelocities){
	if (!root)
		return;

	for (uint i=0;i<root->cJoints.size();i++)
		root->cJoints[i]->fixJointConstraints(fixOrientations, fixVelocities, true);
}

/**
	This method is used to get all the joints in the articulated figure and add them to the list of joints that is passed in as a paramter.
*/
void ArticulatedFigure::addJointsToList(DynamicArray<Joint*> *joints){
	if (!root)
		return;
	DynamicArray<ArticulatedRigidBody*> bodies;
	bodies.push_back(root);

	int currentBody = 0;

	while ((uint)currentBody<bodies.size()){
		//add all the children joints to the list
		for (uint i=0;i<bodies[currentBody]->cJoints.size();i++){
			joints->push_back(bodies[currentBody]->cJoints[i]);
			bodies.push_back(bodies[currentBody]->cJoints[i]->child);
		}
		currentBody++;
	}
}

/**
	This method is used to compute the total mass of the articulated figure.
*/
void ArticulatedFigure::computeMass(){
	double curMass = root->getMass();
	double totalMass = curMass;
	DynamicArray <Joint*> joints;

	this->addJointsToList(&joints);

	for (uint i=0; i < joints.size(); i++){
		curMass = joints[i]->child->getMass();
		totalMass += curMass;
	}

	mass = totalMass;
}

/**
	This method is used to get the total mass of the articulated figure.
*/
double ArticulatedFigure::getMass(){
	return mass;
}

/**
	This method is used to load the details of an articulated figure from file. The PhysicalWorld parameter points to the world in which the objects
	that need to be linked live in.
*/
void ArticulatedFigure::loadFromFile(FILE* f, AbstractRBEngine* world){
	if (f == NULL)
		throwError("Invalid file pointer.");
	if (world == NULL)
		throwError("A valid physical world must be passed in as a parameter");
	//have a temporary buffer used to read the file line by line...
	char buffer[200];
	char tempName[100];
	Joint* tempJoint;

	//this is where it happens.
	while (!feof(f)){
		//get a line from the file...
		fgets(buffer, 200, f);
		if (strlen(buffer)>195)
			throwError("The input file contains a line that is longer than ~200 characters - not allowed");
		char *line = lTrim(buffer);
		int lineType = getRBLineType(line);
		switch (lineType) {
			case RB_ROOT:
				sscanf(line, "%s", tempName);
				if (root != NULL)
					throwError("This articulated figure already has a root");
				root = world->getARBByName(tempName);
				if (root == NULL)
					throwError("The articulated rigid body \'%s\' cannot be found!", tempName);
				break;
			case RB_JOINT_TYPE_UNIVERSAL:
				tempJoint = new UniversalJoint(line);
				tempJoint->loadFromFile(f, world);
				tempJoint->child->AFParent = this;
				tempJoint->parent->AFParent = this;
				break;
			case RB_JOINT_TYPE_HINGE:
				tempJoint = new HingeJoint(line);
				tempJoint->loadFromFile(f, world);
				tempJoint->child->AFParent = this;
				tempJoint->parent->AFParent = this;
				break;
			case RB_JOINT_TYPE_BALL_IN_SOCKET:
				tempJoint = new BallInSocketJoint(line);
				tempJoint->loadFromFile(f, world);
				tempJoint->child->AFParent = this;
				tempJoint->parent->AFParent = this;
				break;
			case RB_END_ARTICULATED_FIGURE:
				//make sure that the root does not have a parent, otherwise we'll end up with loops in the articulated figure]
				if (root->pJoint != NULL)
					throwError("The root of the articulated figure is not allowed to have a parent!");
				return;//and... done
				break;
			case RB_NOT_IMPORTANT:
				if (strlen(line)!=0 && line[0] != '#')
					tprintf("Ignoring input line: \'%s\'\n", line);
				break;
			default:
				throwError("Incorrect articulated body input file: \'%s\' - unexpected line.", buffer);
		}
	}
	throwError("Incorrect articulated body input file! No /ArticulatedFigure found");
}

