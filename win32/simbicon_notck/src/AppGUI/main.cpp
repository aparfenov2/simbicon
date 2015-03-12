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

/*
 * main.cpp: The main entry of the program.
 */
#include <windows.h>
#include "UI.h"
//#include "tcltk.h"
#include "tchar.h"

/**
 *	Entry point for the program. Note that we will not worry much about the command line arguments.
 */
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
//	char *argv[] = {"Framework"};
//	int argc = 1;
//
//	if( *lpCmdLine == 'n' ) {
//		Globals::useShader = false;
//		Globals::useConsole = false;
//	}
//
//	if( *lpCmdLine == 's' ) {
//		Globals::useShader = true;
//		Globals::useConsole = false;
//	}
//
//
//	try{
////		Tk_Main(argc, argv, Tcl_AppInit);
//	}catch(char* msg){
//		logPrint("Exception: %s\n", msg);
//	}
//    
//    return 0;
//}


int main(int argc, char* argv[]) {
	InitMainWindow(argc, (const char **)argv);
	Globals::animationRunning = 1;
	Globals::followCharacter = 1;
	Globals::drawGroundPlane = 1;
	glutMainLoop();
}