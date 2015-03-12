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

#include ".\universaljoint.h"
#include <Utils/Utils.h>

#define ANGLE_A_CONSTRAINT		1
#define ANGLE_B_CONSTRAINT		2

UniversalJoint::UniversalJoint(char* axes){
	readAxes(axes);
	minAngleA = 0;
	maxAngleA = 0;
	minAngleB = 0;
	maxAngleB = 0;
}

UniversalJoint::~UniversalJoint(void){

}



/**
	This method is used to pass in information regarding the rotation axes. The string that is passed in is expected to have
	been read from an input file.
*/
void UniversalJoint::readAxes(char* axes){
	if (sscanf(axes, "%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z) != 6)
		throwError("Universal joints require two rotation axes to be provided as parameters!");

	a.toUnit();
	b.toUnit();
}

/**
	This method is used to pass information regarding the joint limits for a joint. The string that is passed in is expected to
	have been read from an input file.
*/
void UniversalJoint::readJointLimits(char* limits){
	if (sscanf(limits, "%lf %lf %lf %lf", &minAngleA, &maxAngleA, &minAngleB, &maxAngleB)!=4)
		throwError("Universal joints require 4 joint limites (minAngleA, maxAngleA, minAngleB, maxAngleB)!");
	else
		useJointLimits = true;
}

//FILE* fp = fopen("jointAng.txt","w");

/**
	This method is used to fix the joint angular constraint to correct for drift. This is done by changing
		the orientation of the child.
*/
void UniversalJoint::fixAngularConstraint(const Quaternion& qRel){
	//to go from the child's coord frame to its parent, first rotate around the axis b, then around the axis a.
	Quaternion tmpQ1, tmpQ2;
	//compute two rotations, such that qRel = tmpQ1 * tmpQ2, and tmpQ2 is a rotation about the vector b (expressed in child coordinates)
	qRel.decomposeRotation(&tmpQ1, &tmpQ2, b);

	//now make sure that tmpQ1 represents a rotation about axis a (expressed in parent coordinates)
	double angA = tmpQ1.getRotationAngle(a);
	Vector3d tmpV1 = tmpQ1.v;
	tmpV1.toUnit();
	double mod = tmpV1.dotProductWith(a);
	if (mod < 0) mod = -mod;
	angA *= mod;
	child->state.orientation = parent->state.orientation * Quaternion::getRotationQuaternion(angA, a) * tmpQ2;
}

