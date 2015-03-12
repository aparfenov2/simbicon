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

#include <GLUtils/GLMesh.h>


/*======================================================================================================================================================================*
 | This class implements the routines that are needed to load a mesh from an OBJ file. This class loads a GLMesh with the polygonal mesh that is stored in a file.      |
 | Only vertex coordinates, vertex texture coordinates and connectivity information are loaded from the file.                                                           |
 *======================================================================================================================================================================*/
class OBJReader{
public:
	OBJReader(void);
	~OBJReader(void);

	/**
		This static method reads an obj file, whose name is sent in as a parameter, and returns a pointer to a GLMesh object that it created based on the file information.
		This method throws errors if the file doesn't exist, is not an obj file, etc.
	*/
	static GLMesh* loadOBJFile(const char* fileName);
};
