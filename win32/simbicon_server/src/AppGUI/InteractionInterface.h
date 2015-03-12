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

#include <GLUtils/GLTexture.h>
#include <Utils/Timer.h>
#include <mathLib/Vector3d.h>

/**
	This class is used to display an openGL sub-window that the user can interact with by clicking on it. When a mouse event takes place,
	this class can process it, and returns a vector that represents the location, relative to the center of the sub-window, of the mouse click.
	This information can then be processed in whatever way is desired.
*/
class InteractionInterface{
private:
	//The background for the interaction interface is given by this texture.
	GLTexture* interfaceBg;

	//this is the size of the interface
	int size;

	//and this is where the sub-window should appear in the main window
	int posX, posY;

	//the center-most portion of the interface can optionally remain unused. This is the radius of the unused region
	double unusedCenter;

	//when a mouse is clicked, we will still be drawing the feedback arrow for a bit. We'll use this timer for that.
	Timer t;
	//and this is the vector that we should be drawing
	Vector3d inputVector;

public:
	InteractionInterface(char* bgName, int posX, int posY, int size);
	~InteractionInterface(void);

	/**
		This method is used to draw the interaction interface
	*/
	void drawInterface();

	/**
		This method is used to process a mouse event - we'll treat all of them the same. The mouse coordinates
		are assumed to be passed in window coordinates. If the mouse is outside of the interaction interface,
		this method returns false and does not modify result. Otherwise this method returns false, and result
		will be set to the vector from the mouse click to the center of the window.
	*/
	bool handleMouseEvent(int mouseX, int mouseY, Vector3d* result);

};



