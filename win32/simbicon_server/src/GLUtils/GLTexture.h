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

#include <Include/glHeaders.h>


/*----------------------------------------------------------------------------------------------------------------------*
 * Instances of this class will be used to easily use texture mapping (2D textures) for OpenGL applications.            *
 *----------------------------------------------------------------------------------------------------------------------*/

class GLTexture  {
private:
	//this will act as a reference to the current texture that was created by opengl
	GLuint texID;
	//
public:
	/*
		The constructor takes as input the name of a .bmp file that contains the texture to be loaded.
		This constructor throws errors if the file cannot be found, or if it's height and width are not powers of 2
	*/
	GLTexture(char* fileName);
	
	/*
		destructor
	*/
	~GLTexture(void);

	/*
		this method sets the current texture as the active
	*/
	void activate();

};
