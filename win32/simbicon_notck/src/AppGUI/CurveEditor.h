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



#include <Core/Trajectory.h>

#include "SubGLWindow.h"

/**
  * This class is used to draw a simple curve editor in the OpenGL window.
  */
class CurveEditor : public SubGLWindow {

protected:

	// True if the curve editor holds the control over the mouse (after a mouse down and before the mouse up)
	bool holdMouse;

	// Index of the control point held by the mouse (-1 if holding the background)
	int pointHeldIdx;

	// Position where background is being help, in pixel
	int holdPosX, holdPosY;

	// The trajectory to display and edit
	Trajectory1D* trajectory;



public:


	/**
		Default constructor
	*/
	CurveEditor( int posX, int posY, int sizeX, int sizeY );

	/**
		Attaches a trajectory to be edited
		The CurveEditor doesn't own the trajectory and the caller is responsible for destroying
		the trajectory. If the trajectory is destroyed, the editor should be notified by passing "null"
	*/
	void setTrajectory( Trajectory1D* trajectory );


	/** 
		Draw the curve editor in the top-left corner of the OpenGL window
	*/
	void draw();


	/**
		This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
		The coordinates are relative to top-left (OpenGL are usually relative to bot-left)
		Returns false if the event is not handled, true if it was handled
	*/
	bool onMouseEvent(int eventType, int button, int mouseX, int mouseY);

};