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

/*==================================================================================================================================================*
 | This abstract class presents the methods that need to be implemented by the extending classes - classes which will be used for imageIO using     |
 | different image formats.                                                                                                                         |
 *==================================================================================================================================================*/

#define RGB_MODEL 0
#define RGBA_MODEL 1


#include "Image.h"
#include <string.h>
#include <stdlib.h>

class ImageIO  {
protected:
	//the file name of the image to be written or read
	char* fileName;
public:
	ImageIO(char* fileName){
		this->fileName = strdup(fileName);
	}
	~ImageIO(void){
		if (this->fileName != NULL)
			free(fileName);
	}

	/**
		This method should be implemented by the extending classes - it will load an image from the given file.
		The imageModel indicates whether the image will be an RGB or RGBA image.
	*/
	virtual Image* loadFromFile(int imageModel = RGB_MODEL) = 0;
	/**
		This method should be implemented by the extending classes - it will save an image in a specific file format.
	*/
	virtual void writeToFile(Image* img) = 0;
};
