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
 * This class is used to implement a hinge joint - angular impulses that allow relative rotation between the parent and the child only around a given axis must be      *
 * computed.                                                                                                                                                            *
 *======================================================================================================================================================================*/
class Joint;
class HingeJoint : public Joint{
friend class ODEWorld;
private:
/**
	Quantities that do not change
*/
	//This joint only allows relative motion about axis a - stored in parent coordinates
	Vector3d a;
	//keep track of the joint limits as well - min and max allowed angles around the rotation axis
	double minAngle;
	double maxAngle;

public:
	HingeJoint(char* axes);
	virtual ~HingeJoint(void);

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
		Returns the type of the current joint
	*/
	virtual int getJointType(){return HINGE_JOINT;}


};
