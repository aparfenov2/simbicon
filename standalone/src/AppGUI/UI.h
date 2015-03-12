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

/**
 *  UI.h: The user interface for this application is made up of a tk console, a tcl toolbar, and a GLUT-based frame
 *  that uses OpenGL for rendering. This file, together with the associated .cpp file implement methods that are
 *  necessary to set up and start the application.
 */
#pragma once

#include "Globals.h"

//// Quit the application
//int quit (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv);
//
//
//// Start/Pause/Restart the animation
//int animate _ANSI_ARGS_((ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv));
//
//// Launch the animation
//int launch (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv);
//
//// control the camera orientation
//int camera (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv);
//
////this method is used to manipulate the state of the animation
//int animation (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv);
//
//// control the camera orientation
//int instantChar (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv);


void InitMainWindow(int argc, const char **argv);

/**
 *	This method is responsible with initiating the work that needs to be done before one new frame is drawn. 
 */
void appProcess(void);

/**
	This method gets called when the GL window should be redisplayed.
*/
void appRender(void);

/**
 * Processes TCL/TK events. 
 */
//void CheckTCLTKEvents();

/**
	This is the callback method for mouse events
*/
void processMouse(int button, int state, int x, int y);

/**
	This is the callback method for mouse (drag) events
*/
void processMouseActiveMotion(int x, int y);


/**
	This is the callback method for keyboard events
*/
void processKeyboard(unsigned char key, int x, int y);

void processPassiveMouseActiveMotion(int x, int y);