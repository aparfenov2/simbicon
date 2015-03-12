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

#include "Application.h"
#include <AppGUI/Globals.h>


/**
 * Constructor.
 */
Application::Application(void){


}

/**
 * Destructor.
 */
Application::~Application(void){

}


/**
 * This method is called whenever the system wants to draw the current frame to an obj file
 * The file is already opened and the header is written, the application should only output
 * vertices and faces
 *
 * vertexIdxOffset indicates the index of the first vertex for this object, this makes it possible to render
 * multiple different meshes to the same OBJ file
 *
 * This is a fallback-default method that should be overriden by all subclasses.
 * Subclasses shouldn't call this method.
 *
 * Returns the number of vertices written to the file
 */
uint Application::renderToObjFile(FILE* fp, uint vertexIdxOffset) {

	fprintf( fp, "# Render to OBJ file not supported!\n\n" );

	return 0;
}




/**
 * This method gets called when the application gets initialized.
 */
void Application::init(){
}

/**
 * This method is used to restart the application.
 */
void Application::restart(){

}

/**
 * This method is used to reload the application.
 */
void Application::reload(){

}

/**
 * This method will get called on idle. This method should be responsible with doing the work that the application needs to do 
 * (i.e. run simulations, and so on).
 */
void Application::processTask(){
	//nothing to do here...
}

