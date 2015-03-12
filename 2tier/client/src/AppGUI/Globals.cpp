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

#include "Globals.h"

//initialize the static variables to some sensible values
Application* Globals::app = NULL;
int Globals::animationRunning = 0;
double Globals::animationTimeToRealTimeRatio = 1;
double Globals::desiredFrameRate = 30;

//double Globals::dt = 1.0/(6000.0);
int Globals::drawFPS = 1;
int Globals::drawCubeMap = 0;
int Globals::drawGlobalAxes = 0;
int Globals::drawShadows = 1;
int Globals::drawCollisionPrimitives = 0;
int Globals::drawGroundPlane = 0;
int Globals::followCharacter = 0;
int Globals::drawJoints = 0;
int Globals::drawContactForces = 0;
int Globals::drawDesiredPose = 0;
double Globals::targetPosePhase = 0;
int Globals::drawPushInterface = 0;
int Globals::drawCurveEditor = 0;
int Globals::drawCanvas = 0;
int Globals::drawScreenShots = 0;
int Globals::drawWorldShots = 0;
int Globals::drawControlShots = 0;
int Globals::updateDVTraj = 0;
char* Globals::currControlShotStr = NULL;
bool Globals::useShader = true;
bool Globals::useConsole = true;

double Globals::a=0, Globals::b=1, Globals::c=0, Globals::d=0;

Globals::Globals(void){
}

Globals::~Globals(void){

}


