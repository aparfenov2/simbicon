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
#include <mathLib/Quaternion.h>
#include <Utils/Timer.h>
#include <GLUtils/GLCamera.h>


/**
 * This calss implements the basic operations that are needed for an OpenGL window. It is used to initialize OpenGL, 
 * the lights, the camera, display the objects in the world, etc. 
 */
class GLWindow{
private:
	//sets up the opengl window
	virtual void setupOpenGL();
	//we will want to rotate the camera with the mouse, so we'll keep track of the last location of the mouse cursor
	int oldMouseX, oldMouseY;
	//and this is the button that was pressed...
	int mouseButtonPressed;

	//the camera that we will be using
	GLCamera camera;

	//in order to avoid writing the a new fps rate at every redraw, we will instead compute averages and display those. We need:
	//the total ellapsedTime since the last update
	double ellapsedTime;
	//the frame rate that is currently being displayed
	double oldFrameRate;
	//the number of frames that we've counted so far
	int nrFramesSinceUpdate;
	//the total time spent processing
	double processingTime;
	//and the processing time that we are displaying
	double oldPerformanceRate;
	//this is the time the processing took (try to ignore external delays as much as possible)
	double timeSpentProcessing;

	//keep a timer here to see how long it's been since the last redraw
	Timer fpsTimer;

	//draw information regarding the frame rate and performance
	void drawFPSandPerf(double timeSinceLastUpdate, double timeSpentProcessing);

	//draw the background cube map
	void drawCubeMap();

	//draw the global axes
	void drawAxes();

	//draws the shadows, by projecting the scene on the ground. Only works for planar ground surfaces!
	void drawShadows();

	//keep track of the width, height, x and y position of the window
	int x, y, w, h;

public:
    //Draw the window
    virtual void draw();
	//constructor
	GLWindow(int x, int y, int w, int h);
	//destructor
	~GLWindow(void);

	//this method is used to compute the correct camera transformation, and prepare the modelview matrix accordingly
	void setupGLCamera();

	//this method is used to set up the lights (position, direction, etc)
	void setupLights();

	//this method is used to initialize the gl window
	virtual void init();

    // Handle mouse events
    virtual int onMouseEvent(int mEvent, int button, int x, int y);

    // Handle keyboard events
    virtual int onKeyEvent(int character);


	//this method is called immediately before the application takes its turn to process its task
	void onStartProcessing();
	//and this method is called immediately after the application processed its task
	void onStopProcessing();


	//this method is used to set the desired rotation values for the camera
	void setCameraRotation(const Vector3d& newRot);
	//and this method is used to set the target that the camera looks at
	void setCameraTarget(const Point3d& newTarget);

	inline int getW(){
		return w;
	}
	inline int getH(){
		return h;
	}
};
