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


#include "InteractiveWorld.h"
#include <GLUtils/GLMesh.h>
#include <GLUtils/OBJReader.h>
#include <Utils/Utils.h>
#include "Globals.h"
#include <Core/SimBiConFramework.h>
#include <Utils/Utils.h>

/**
 * Constructor.
 */
InteractiveWorld::InteractiveWorld(void){
	bInterface = NULL;
	world = NULL;
}

/**
 * Destructor.
 */
InteractiveWorld::~InteractiveWorld(void){
	delete bInterface;
}

/**
 * This method is used to draw extra stuff on the screen (such as items that need to be on the screen at all times)
 */
void InteractiveWorld::drawExtras(){
	if (Globals::drawPushInterface == 1 && bInterface)
		bInterface->drawInterface();
}

/**
 * This method gets called when the application gets initialized. 
 */
void InteractiveWorld::init(){
	Application::init();

	bInterface = new InteractionInterface("../data/textures/pushInterface.bmp", 0, 0, 128);
}


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
uint InteractiveWorld::renderToObjFile(FILE* fp, uint vertexIdxOffset) {
	if (world)
		return world->renderRBsToObjFile(fp, vertexIdxOffset);
	else
		return 0;


}


/**
 *	This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
 */
bool InteractiveWorld::onMouseEvent(int eventType, int button, int mouseX, int mouseY){
	//need to figure out if the mouse is in the push interface window (and if we care)...
	if (Globals::drawPushInterface == 1 && button == MOUSE_LBUTTON && eventType != MOUSE_UP){
		Vector3d input;
		Point3d p;
		if (bInterface == false){
			tprintf("Warning: No interaction interface was created!\n");
			return false;
		}

		if (world == NULL){
			tprintf("Warning: There is no valid reference to a world!\n");
			return false;
		}

		RigidBody* dBall = world->getRBByName("dodgeBall");
		if (dBall == NULL){
			tprintf("Warning: No dodgeBall loaded!\n");
			return false;
		}

		bool eventHandled = bInterface->handleMouseEvent(mouseX, mouseY, &input);
		if (eventHandled ){
			if (input.length() > 0){
				//get the object that we will be throwing...
				getDodgeBallPosAndVel(-input.x, input.y, input.length(), &p, &input);
				dBall->setCMPosition(p);
				dBall->setCMVelocity(input);
//				dBall->updateToWorldTransformation();
			}
			return true;
		}
	}
	return false;
}



