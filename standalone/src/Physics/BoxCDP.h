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

#include <Physics/CollisionDetectionPrimitive.h>
#include <MathLib/Point3d.h>
#include <MathLib/TransformationMatrix.h>
#include <Utils/Utils.h>

/*========================================================================================================================================================================*
 * This class implements a rectangular box class that will be used as a collision detection primitive.                                                                    *
 * A box is represented by the position of two opposite corners.                                                                                                          *
 *========================================================================================================================================================================*/
class BoxCDP : public CollisionDetectionPrimitive{
private:
	//these are the two corners of the box, expressed in local coordinates.
	Point3d p1, p2;
	
public:
	BoxCDP(RigidBody* theBdy, Point3d& p1_, Point3d& p2_);
	virtual ~BoxCDP(void);

	virtual void updateToWorldPrimitive(){}

	/**
		Draw an outline of the box
	*/
	virtual void draw();

	/**
		return the center of the box, expressed in local coordinates
	*/
	inline Point3d getCenter(){
		return Point3d((p1.x+p2.x)/2, (p1.y+p2.y)/2, (p1.z+p2.z)/2);
	}

	/**
		returns the length in the x-direction
	*/
	inline double getXLen(){
		return (fabs(p1.x-p2.x));
	}

	/**
		returns the length in the y-direction
	*/
	inline double getYLen(){
		return (fabs(p1.y-p2.y));
	}

	/**
		returns the length in the z-direction
	*/
	inline double getZLen(){
		return (fabs(p1.z-p2.z));
	}


};

