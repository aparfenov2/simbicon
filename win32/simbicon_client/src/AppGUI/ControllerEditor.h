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
//#include "CurveEditor.h"

/**
  * This class is used to build ControllerFramework and use it to control articulated figures.
  */
class ControllerEditor : public InteractiveWorld {
protected:
	//this is the physical world that contains all the objects inside
	SimBiConFramework* conF;

	//this array will be used to save/load the state of the dynamic world
	DynamicArray<double> worldState;

	//this is the name of the input file
	char inputFile[100];

	//this is the initial state of the framework...
	SimBiConFrameworkState conState;

	// This indicates the number of the future control shot and the maximal number of shots
	int nextControlShot;
	int maxControlShot;

	//keep track of the two variables below to report the speed of the character
	double avgSpeed;
	int timesVelSampled;


	// These trajectories are reset after every cycle
	// dTrajX and vTrajX are sign-reversed on right stance cycles
	Trajectory1D dTrajX;
	Trajectory1D dTrajZ;
	Trajectory1D vTrajX;
	Trajectory1D vTrajZ;

	// Contains the FSM state index of the last simulation step
	int lastFSMState;


public:
	/**
	 * Constructor.
	 */
	ControllerEditor(void);

	/**
	 * Destructor.
	 */
	virtual ~ControllerEditor(void);


	/**
	 * This method is used to create a physical world and load the objects in it.
	 */
	virtual void loadFramework();

	/**
	 * This method is used to create a physical world and load the objects in it.
	 */
	void loadFramework( int controlShot );


	/**
	 * Registers TCL functions specific to this application
	 */
//	void registerTclFunctions();


	inline SimBiConFramework* getFramework(){
		return conF;
	}

	/**
	 * This method gets called when the application gets initialized. 
	 */
	virtual void init();


	/**
	* This method will get called on idle. This method should be responsible with doing the work that the application needs to do 
	* (i.e. run simulations, and so on).
	*/
	virtual void processTask();




};




