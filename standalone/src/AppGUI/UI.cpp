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

#include <stdio.h>
#include <string.h>
#include "UI.h"
#include "GLWindow.h"
#include "Application.h"
#include "ControllerEditor.h"
#include "Globals.h"
#include <include/GLheaders.h>

/**
 * This method is used to initialize the main window.
 */
void InitMainWindow(int argc, const char **argv){
	int width = 800;
	int height = 600;
	if (argc>3){
		sscanf(argv[2], "%d", &width);
		sscanf(argv[3], "%d", &height);
	}

	//create the GLUT window...
	glutInit(&argc, (char **)argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Simbicon 1.5 Controller Editing Framework");

	//set up the callback methods
	glutDisplayFunc(appRender);
	glutIdleFunc(appProcess);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processPassiveMouseActiveMotion);
	glutKeyboardFunc(processKeyboard);

	//and an openGL window that we will use for rendering
	Globals::window = new GLWindow(0, 0, width, height);
	Globals::window->init();

	//also create an application that will be used to run the whole thing.
	//if (strcmp(argv[1], "ControllerEditor") == 0)
		Globals::app = new ControllerEditor();
	//else
//		Globals::app = new Application();

	Globals::app->init();
}

/**
	This is the callback method for mouse events
*/
void processMouse(int button, int state, int x, int y){
	int mButton = MOUSE_LBUTTON;
	int mEvent = MOUSE_UP;
	if (button == GLUT_RIGHT_BUTTON) mButton = MOUSE_RBUTTON;
	if (button == GLUT_MIDDLE_BUTTON) mButton = MOUSE_MBUTTON;
//	if (button == GLUT_WHEEL_DOWN) mButton = MOUSE_WHEEL_DOWN;
//	if (button == GLUT_WHEEL_UP) mButton = MOUSE_WHEEL_UP;
	if (state == GLUT_DOWN) mEvent = MOUSE_DOWN;
	if (Globals::window)
		Globals::window->onMouseEvent(mEvent, mButton, x, y);
}

/**
	This is the callback method for mouse (drag) events
*/
void processMouseActiveMotion(int x, int y){
	if (Globals::window)
		Globals::window->onMouseEvent(MOUSE_DRAG, -1, x, y);
}


/**
	This is the callback method for mouse (drag) events
*/
void processPassiveMouseActiveMotion(int x, int y){
	if (Globals::window)
		Globals::window->onMouseEvent(MOUSE_MOVE, -1, x, y);
}

void processKeyboard(unsigned char key, int x, int y){
	if (Globals::window)
		Globals::window->onKeyEvent((int)key);
}

/**
	This method gets called when the GL window should be redisplayed.
*/
void appRender(void){
	if (Globals::window)
		Globals::window->draw();
	glutSwapBuffers();
}

/**
 *	This method is responsible with initiating the work that needs to be done before one new frame is drawn.
 */
void appProcess(void){
	//we will check the tk/tcl messages as well...
//	CheckTCLTKEvents();

	if (!Globals::window || !Globals::app)
		return;

	Globals::window->onStartProcessing();

	//we will only process the task if the animation should be running
	if (Globals::animationRunning == 1)
		(Globals::app)->processTask();

	Globals::window->onStopProcessing();

	if (Globals::followCharacter)
		Globals::window->setCameraTarget(Globals::app->getCameraTarget());

	//check the tk/tcl messages again
//	CheckTCLTKEvents();


	//force a redraw now...
	glutPostRedisplay();
}

///**
// * terminate the application.
// */
//int quit (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv){
//	exit(0);
//	return TCL_OK;
//}
//
//
///**
//  * setup the camera orientation
//  */
//int camera (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv){
//    if (argc < 2) {
//        Tcl_AppendResult(interp, "Usage: view c_front|c_side|c_45|c_back");
//        return TCL_OK;
//    }
//
//	if (!Globals::window)
//		return TCL_OK;
//
//	if (strcmp(argv[1], "c_front") == 0){
//		Globals::window->setCameraRotation(Vector3d(0,0,0));
////		Globals::window->redraw();
//	}
//
//	if (strcmp(argv[1], "c_side") == 0){
//		Globals::window->setCameraRotation(Vector3d(0,-PI/2,0));
////		Globals::window->redraw();
//	}
//
//	if (strcmp(argv[1], "c_45") == 0){
//		Globals::window->setCameraRotation(Vector3d(0,-PI/4,0));
////		Globals::window->redraw();
//	}
//
//	if (strcmp(argv[1], "c_n45") == 0){
//		Globals::window->setCameraRotation(Vector3d(0,-3*PI/4,0));
////		Globals::window->redraw();
//	}
//
//	if (strcmp(argv[1], "c_back") == 0){
//		Globals::window->setCameraRotation(Vector3d(0,PI,0));
////		Globals::window->redraw();
//	}
//
//	return TCL_OK;
//}
//
/////////////////////////////////////////////////////////////
//// Start|Stop the animation
/////////////////////////////////////////////////////////////
//int animation (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv){
//    if (argc < 2) {
//        Tcl_AppendResult(interp, "Usage: anim start|stop|step|restart");
//        return TCL_OK;
//    }
//
//	if (strcmp(argv[1], "start") == 0){
//		if (Globals::animationRunning == 0){
//			tprintf("Starting animation!\n");
//		}
//		Globals::animationRunning = 1;
//	}
//	else if(strcmp(argv[1], "pause") == 0){
//		if (Globals::animationRunning == 1){
//			tprintf("Animation paused!\n");
//		}
//		Globals::animationRunning = 0;
//	}
//	else if(strcmp(argv[1],"step")==0){
//		if (Globals::animationRunning == 0){
//			tprintf("Advancing the animation!\n");
//			if (Globals::app)
//				Globals::app->processTask();
//		}
//	}
//	else if (strcmp(argv[1], "restart") == 0){
//		tprintf("Restarting the animation!\n");
//		if (Globals::app)
//			Globals::app->restart();
//	}
//	else if (strcmp(argv[1], "reload") == 0){
//		tprintf("Reloading the animation!\n");
//		if (Globals::app)
//			Globals::app->reload();
//	}
//
//	return TCL_OK;
//}
//
//
///**
// * This method is used to launch the animation
// */
//int launch (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv){
//    if (argc < 2) {
//        tprintf("Usage: launch Simbicon3D | mocap");
//        return TCL_OK;
//    }
//	InitMainWindow(argc, argv);
//
//    return TCL_OK;
//}
//
///**
//  * setup the camera orientation
//  */
//int instantChar (ClientData clientData, Tcl_Interp *interp, int argc, CONST84 char **argv){
// 
//    if (argc < 1) {
//        Tcl_AppendResult(interp, "Usage: instantChar");
//        return TCL_OK;
//    }
//
//    return TCL_OK;
//}

