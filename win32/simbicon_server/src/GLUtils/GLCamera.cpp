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

#include "GLCamera.h"
#include <include/GLheaders.h>


GLCamera::GLCamera(void){
	//initialize to the identity quaternion
	orientation = Quaternion(1, 0, 0, 0);
	camDistance = -4;
	target = Point3d(0,0,0);
	rotations = Vector3d(0,0,0);
}

GLCamera::~GLCamera(void){
}


//this method is used to apply the transofmations 
void GLCamera::applyCameraTransformations(){
	//build the orientation. We will construct it by rotating about the z axis, y axis first, and the x
	orientation = Quaternion::getRotationQuaternion(rotations.z, Vector3d(0, 0, 1))
				* Quaternion::getRotationQuaternion(rotations.y, Vector3d(0, 1, 0))
				* Quaternion::getRotationQuaternion(rotations.x, Vector3d(1, 0, 0));
	//we know we are looking down the z-axis of the camera coordinate frame. So we need to compute what that axis is in world coordinates.
	Vector3d zW = orientation.rotate(Vector3d(0,0,-1));
	//this is the camera's up vector, expressed in world coordinates 
	Vector3d yW = orientation.rotate(Vector3d(0,1,0));
	//we know where we are looking, so we can compute the position of the camera in world coordinates.
	Point3d camPos = target + zW * camDistance;
	//now we have all the information we need: the camera coordinate frame expressed in world coordinates. Need only invert it...
	gluLookAt(camPos.x, camPos.y, camPos.z, target.x, target.y, target.z, yW.x, yW.y, yW.z);
	double vals[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, vals);
	worldToCam.setOGLValues(vals);
}

