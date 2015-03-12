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

/*==============================================================================================================================================================*
 * This class implements a ball in socket joint type.                                                                                                           *
 *==============================================================================================================================================================*/
class BallInSocketJoint : public Joint{
friend class ODEWorld;
private:
/**
	Quantities that do not change
*/

	//BallInSocket joints are free to rotate about any axis. However, in order to be able to apply joint limits, we will 
	//identify some axis, about which we will place joint limits. In particular, we'll use a swing and twist decomposition
	//of the relative orientations between the two bodies of a hinge joint

	//these two axes define the plane of vectors along which the rotations represent a swing - stored in parent coordinates
	Vector3d swingAxis1, swingAxis2;
	//and this one is stored in child coordinates - this is the twist axis
	Vector3d twistAxis;
	//and the min and max allowed angles along the two swing axes (define an ellipsoid that can be offset if the min/max angles are not equal in magnitude)
	double minSwingAngle1, maxSwingAngle1, minSwingAngle2, maxSwingAngle2;
	//and limits around the twist axis
	double minTwistAngle, maxTwistAngle;
public:
	BallInSocketJoint(char* axes);
	~BallInSocketJoint(void);

	/**
		This method is used to fix the joint angular constraint to correct for drift. This is done by changing
		the orientation of the child.
	*/
	virtual void fixAngularConstraint(const Quaternion& qRel);

	/**
		This method is used to pass information regarding the joint limits for a joint. The string that is passed in is expected to
		have been read from an input file.
	*/
	virtual void readJointLimits(char* limits);

	/**
		This method is used to pass in information regarding the rotation axes. The string that is passed in is expected to have
		been read from an input file.
	*/
	virtual void readAxes(char* axes);

	/**
		Returns the type of the current joint
	*/
	virtual int getJointType(){ return BALL_IN_SOCKET_JOINT;}

};
