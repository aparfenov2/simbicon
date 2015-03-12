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

#include ".\gltexture.h"
#include <Utils/BMPIO.h>
#include <Utils/Image.h>
#include <Utils/Utils.h>


#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

/**
	This method checks the int value that is passed in as a parameter, and returns true if it is one of
	64, 128, 256 or 512, false otherwise
*/
bool checkTexSize(int x){
	return (x == 64 || x == 128 || x == 256 || x == 512 || x == 1024 || x ==2048);
}


/*
	The constructor takes as input the name of a .bmp file that contains the texture to be loaded.
	This constructor throws errors if the file cannot be found, or if it's height and width are not powers of 2
*/
GLTexture::GLTexture(char* fileName){
	//load the image
	BMPIO b(fileName);
	Image* im = b.loadFromFile();

	texID = 0;

	//and generate the texture...
	glGenTextures(1, &texID);

	activate();

	if (!checkTexSize(im->getWidth()) || !checkTexSize(im->getHeight()) || im->getNrBytes()!=3){
		throwError("Wrong texture dimension or nr bits in file \'%s\'", fileName);
	}


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//	glTexImage2D(GL_TEXTURE_2D, 0, 3, im->getWidth(), im->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, im->getDataPointer());

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, im->getWidth(), im->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, im->getDataPointer());

	delete im;
}
/*
	Destructor...
*/
GLTexture::~GLTexture(void){
	glDeleteTextures(1, &texID);
}




/*
	this method sets the current texture as the active
*/
void GLTexture::activate(){
	glBindTexture(GL_TEXTURE_2D, texID);
}


