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

#include <Physics/Joint.h>

/*======================================================================================================================================================================*
 * This class is used to implement a universal joint - angular impulses that allow only two degrees of freedom between the parent and the child must be computed.       *
 *======================================================================================================================================================================*/

class UniversalJoint : public Joint{
friend class ODEWorld;
private:
	//This joint can only rotate about the vector a, that is stored in parent coordinates
	Vector3d a;
	//or about vector b that is stored in child coordinates
	Vector3d b;
	//and the min and max allowed angles (around a axis)
	double minAngleA, maxAngleA;
	//and around the b axis
	double minAngleB, maxAngleB;

public:
	UniversalJoint(char* axes);
	~UniversalJoint(void);

	/**
		This method is used to pass in information regarding the rotation axes. The string that is passed in is expected to have
		been read from an input file.
	*/
	virtual void readAxes(char* axes);

	/**
		This method is used to pass information regarding the joint limits for a joint. The string that is passed in is expected to
		have been read from an input file.
	*/
	virtual void readJointLimits(char* limits);

	/**
		This method is used to fix the joint angular constraint to correct for drift. This is done by changing
		the orientation of the child.
	*/
	virtual void fixAngularConstraint(const Quaternion& qRel);

	/**
		Return the A rotation axis
	*/
	inline Vector3d getRotAxisA(){return a;}

	/**
		Return the B rotation axis
	*/
	inline Vector3d getRotAxisB(){return b;}


	/**
		Returns the type of the current joint
	*/
	virtual int getJointType(){ return UNIVERSAL_JOINT;}

};


