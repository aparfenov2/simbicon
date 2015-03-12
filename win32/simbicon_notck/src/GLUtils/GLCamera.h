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

#include <mathLib/Vector3d.h>
#include <mathLib/Quaternion.h>
#include <mathLib/Point3d.h>
#include <mathLib/TransformationMatrix.h>


/**
 * This class implements a simple open GL camera. This camera can be used to automatically follow a target, and rotate around it.
 */
class GLCamera{
private:
	//keep track of the orientation of the camera.
	Quaternion orientation;
public:
	GLCamera(void);
	~GLCamera(void);

	//this method is used to apply the transofmations 
	void applyCameraTransformations();

	//to simplify things, we will keep track of the rotation using this vector. This way, we won't need to mix rotations about the x, y and z axis
	Vector3d rotations;
	//and also how far it is along its z axis (assuming that it is looking down the -ve z axis of its local frame)
	double camDistance;
	//we will also keep track of the point we are looking at, in world coordinates
	Point3d target;
	//this is the world to camera transformation matrix, recomputed at every step
	TransformationMatrix worldToCam;
};
