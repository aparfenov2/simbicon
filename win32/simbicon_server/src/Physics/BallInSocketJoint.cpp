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

#include ".\ballinsocketjoint.h"
#include <Utils/Utils.h>

#define ANGLE_A_CONSTRAINT		1
#define ANGLE_B_CONSTRAINT		2


BallInSocketJoint::BallInSocketJoint(char* axes){
	readAxes(axes);
}

BallInSocketJoint::~BallInSocketJoint(void){

}

//FILE* fp = fopen("jointAng.txt", "w");

/**
	This method is used to fix the joint angular constraint to correct for drift. This is done by changing
	the orientation of the child.
*/
void BallInSocketJoint::fixAngularConstraint(const Quaternion& qRel){


	//nothing to fix here (well maybe joint limits at some point)

/**  DEBUG only
	angleB = decomposeRotation(qRel, b, &angleA, &a);


	if (strcmp(this->joint->child->name, "torso") == 0){
		fprintf(fp, "%lf\t%lf\n", angleA, angleB);
		fflush(fp);
	}
*/
}

/**
	This method is used to pass in information regarding the rotation axes. The string that is passed in is expected to have
	been read from an input file.
*/
void BallInSocketJoint::readAxes(char* axes){
	if (sscanf(axes, "%lf %lf %lf %lf %lf %lf %lf %lf %lf",&swingAxis1.x, &swingAxis1.y, &swingAxis1.z, &swingAxis2.x, &swingAxis2.y, &swingAxis2.z, &twistAxis.x, &twistAxis.y, &twistAxis.z) != 9){
		if (sscanf(axes, "%lf %lf %lf %lf %lf %lf",&swingAxis1.x, &swingAxis1.y, &swingAxis1.z, &twistAxis.x, &twistAxis.y, &twistAxis.z) != 6){
			throwError("Ball in socket joints require two or three axis to be specified!");
		}
		else
			swingAxis2 = swingAxis1.crossProductWith(twistAxis);
	}
	swingAxis1.toUnit();
	swingAxis2.toUnit();
	twistAxis.toUnit();
}

/**
	This method is used to pass information regarding the joint limits for a joint. The string that is passed in is expected to
	have been read from an input file.
*/
void BallInSocketJoint::readJointLimits(char* limits){
	int n = sscanf(limits, "%lf %lf %lf %lf %lf %lf", &minSwingAngle1, &maxSwingAngle1, &minSwingAngle2, &maxSwingAngle2, &minTwistAngle, &maxTwistAngle);
	if (n!= 6)
		throwError("Ball in socket joints require 6 joint limit parameters (min/max angle for the three axis)!");

	useJointLimits = true;
}
