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

#include <MathLib/Vector3d.h>
#include <GLUtils/GLTexture.h>

/**
 * This is the class that is responsible with implementing the details of what the program does.
 */
class Application{
private:
	//this is the texture used for the ground
	GLTexture *groundTexture;
public:
	/**
	 * Constructor.
	 */
	Application(void);
	/**
	 * Destructor.
	 */
	~Application(void);

	/**
	 * This method is called whenever the window gets redrawn.
	 */
	virtual void draw(bool shadow = false);

	/**
	 * This method is called whenever the system wants to draw the current frame to an obj file
	 * The file is already opened and the header is written, the application should only output
	 * vertices and faces
	 *
	 * vertexIdxOffset indicates the index of the first vertex for this object, this makes it possible to render
	 * multiple different meshes to the same OBJ file
	 *
	 * Returns the number of vertices written to the file
	 */
	virtual uint renderToObjFile(FILE* fp, uint vertexIdxOffset);

	/**
	 * This metod is used to draw the ground. We need to separate it from the main drawing method because of the shadows.
	 */
	virtual void drawGround();

	/**
	 * This method is used to return the normal to the ground. I don't know what should happen if the ground isn't flat... 
	 * only used for shadow drawing!
	 */
	virtual Vector3d getGroundNormal();

	/**
	 * This method gets called when the application gets initialized. 
	 */
	virtual void init();


	/**
	 * This method is used to restart the application.
	 */
	virtual void restart();

	/**
	 * This method is used to reload the application.
	 */
	virtual void reload();

	/**
	 * This method returns the target that the camera should be looking at
	 */
	virtual Point3d getCameraTarget();

	/**
     *	This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
	 */
	virtual bool onMouseEvent(int eventType, int button, int mouseX, int mouseY);

	/**
	 *  This method is used when a keyboard event gets generated. This method returns true if the message gets processed, false otherwise.
	 */
	virtual bool onKeyEvent(int key);

	/**
	 * This method is used to draw extra stuff on the screen (such as items that need to be on the screen at all times)
	 */
	virtual void drawExtras(){
	}

	/**
	 * This method will get called on idle. This method should be responsible with doing the work that the application needs to do 
	 * (i.e. run simulations, and so on).
	 */
	virtual void processTask();

	/**
	 * Registers TCL functions specific to this application
	 */
//	void registerTclFunctions();

};

