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

#include "ControllerEditor.h"
#include "Globals.h"


/**
 * Constructor.
 */
ControllerEditor::ControllerEditor(void){
	tprintf("Loading Controller Editor...\n");
	strcpy(inputFile,  "init/input.conF");

	loadFramework();

//	Globals::changeCurrControlShotStr( -1 );
	conF->getState(&conState);

	nextControlShot = 0;
	maxControlShot = -1;

//	registerTclFunctions();
}


/**
 * Destructor.
 */
ControllerEditor::~ControllerEditor(void){

	nextControlShot = 0;
	maxControlShot = -1;

}

/**
 * This method is used to create a physical world and load the objects in it.
 */
void ControllerEditor::loadFramework(){
	loadFramework( -1 );
}


/**
 * This method is used to create a physical world and load the objects in it.
 */
void ControllerEditor::loadFramework( int controlShot ){
	this->world = NULL;
	//create a new world, and load some bodies
	try{
		if( controlShot < 0 ) {
			conF = new SimBiConFramework(inputFile, NULL);
		}
		else {
			char conFile[256];
			sprintf(conFile, "..\\controlShots\\cs%05d.sbc", controlShot);
			conF = new SimBiConFramework(inputFile, conFile);
		}
	
		avgSpeed = 0;
		timesVelSampled = 0;

//		Globals::changeCurrControlShotStr( controlShot );
		conF->getState(&conState);
		this->world = conF->getWorld();
	}catch(const char* msg){
		conF = NULL;
		tprintf("Error: %s\n", msg);
		logPrint("Error: %s\n", msg);
	}

}




/**
 * This method gets called when the application gets initialized. 
 */
void ControllerEditor::init(){
	InteractiveWorld::init();
}


/**
* This method will get called on idle. This method should be responsible with doing the work that the application needs to do 
* (i.e. run simulations, and so on).
*/
void ControllerEditor::processTask(){
	double simulationTime = 0;
	double maxRunningTime = 0.98/Globals::desiredFrameRate;
	//if we still have time during this frame, or if we need to finish the physics step, do this until the simulation time reaches the desired value
	while (simulationTime/maxRunningTime < Globals::animationTimeToRealTimeRatio){
		simulationTime += SimGlobals::dt;

		double phi = conF->getController()->getPhase();
		lastFSMState = conF->getController()->getFSMState();
		double signChange = (conF->getController()->getStance() == RIGHT_STANCE)?-1:1;
		Globals::targetPosePhase = phi;
//		Tcl_UpdateLinkedVar( Globals::tclInterpreter, "targetPosePhase" );

//		tprintf("d = %2.4lf, v = %2.4lf\n", conF->con->d.x, conF->con->v.x);

		avgSpeed += conF->getCharacter()->getHeading().getComplexConjugate().rotate(conF->getCharacter()->getRoot()->getCMVelocity()).z;
		timesVelSampled++;

		if (conF) {
			if( phi < dTrajX.getMaxPosition() ) {
				dTrajX.clear();
				dTrajZ.clear();
				vTrajX.clear();
				vTrajZ.clear();
			}
			Vector3d d = conF->getController()->d;
			Vector3d v = conF->getController()->v;
			dTrajX.addKnot( phi, d.x * signChange);
			dTrajZ.addKnot( phi, d.z  );
			vTrajX.addKnot( phi, v.x * signChange );
			vTrajZ.addKnot( phi, v.z  );					

			bool newStep = conF->advanceInTime(SimGlobals::dt);

			if( newStep ) {
				avgSpeed /= timesVelSampled;
				Vector3d v = conF->getLastStepTaken();
				tprintf("step: %lf %lf %lf (phi = %lf, speed = %lf)\n", v.x, v.y, v.z, phi, avgSpeed);
//				Globals::animationRunning = false;

				avgSpeed = 0;
				timesVelSampled = 0;

//				stepTaken();

				//get the reversed new state...
				DynamicArray<double> newState;
				if (conF->getController()->getStance() == RIGHT_STANCE)
					conF->getCharacter()->getReverseStanceState(&newState);
				else
					conF->getCharacter()->getState(&newState);

				ReducedCharacterState rNew(&newState);

				conF->getCharacter()->saveReducedStateToFile("out\\reducedCharacterState.rs", newState);
			}

		}
	}
}




