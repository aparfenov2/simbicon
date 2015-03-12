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

#include "InteractionInterface.h"
#include <GLUtils/GLUtils.h>
#include <math.h>

InteractionInterface::InteractionInterface(char* bgName, int posX, int posY, int size){
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	interfaceBg = new GLTexture(bgName);
	unusedCenter = 0.2;
}

InteractionInterface::~InteractionInterface(void){

}

/**
	This method is used to draw the interaction interface
*/
void InteractionInterface::drawInterface(){
	//we want to always draw the push window in the upper-left corner
	int viewportSettings[4];
	glGetIntegerv(GL_VIEWPORT, viewportSettings);
	glViewport(posX,viewportSettings[3]-size-posY, size, size);

    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glColor3d(1,1,1);
	if (interfaceBg)
		interfaceBg->activate();
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex2d(0,0);
		glTexCoord2d(0,1);
		glVertex2d(0,1);
		glTexCoord2d(1,1);
		glVertex2d(1,1);
		glTexCoord2d(1,0);
		glVertex2d(1,0);
	glEnd();

	glColor3d(1, 0, 0);
	//now draw the arrow...
	if (t.timeEllapsed() < 1){
		Vector3d dir = -inputVector;
		Point3d org = Point3d(0.5, 0.5, 0)+inputVector+inputVector.unit()*unusedCenter;

		GLUtils::drawCylinder(0.015, dir*0.8, org);
		GLUtils::drawCone(0.03, dir/4, org+dir*0.75);
	}

	glPopAttrib();
	glPopMatrix();
    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//set the viewport back to how it was...
    glViewport(viewportSettings[0], viewportSettings[1], viewportSettings[2], viewportSettings[3]);
}

/**
	This method is used to process a mouse event - we'll treat all of them the same. The mouse coordinates
	are assumed to be passed in window coordinates. If the mouse is outside of the interaction interface,
	this method returns false and does not modify result. Otherwise this method returns false, and result
	will be set to the vector from the mouse click to the center of the window.
*/
bool InteractionInterface::handleMouseEvent(int mouseX, int mouseY, Vector3d* result){
		if (mouseX>posX && mouseX<posX + size && mouseY>posY && mouseY<posY + size){
			double rad = size/2;
			//need to figure out where the mouse is, relative to the center of the window, and based on it
			*result = Vector3d(Point3d(mouseX, mouseY, 0), Point3d(rad, rad,0));

			double len = result->length();
			if (len < rad * 2 * unusedCenter){
				*result = Vector3d();
				inputVector = *result;
				t.restart();
				return true;
			}
			len -=  rad * 2 * unusedCenter;
			*result = result->unit() * len;

			rad = (rad - rad * 2 * unusedCenter) * 0.9;

			//now, the window is square, but we will always make sure that we normalize the length, so that we don't get
			//longer vectors at the corners, so we need to modify the length of the vector by this constant, if it is outside
			//of the ellipse defined by the dimension of the window

			double d = SQR(result->x / rad) + SQR(result->y / rad);

			if (d > 1){
				double c = sqrt(1.0 / (d));
				*result *= c;
			}

			result->x /= size;
			result->y /= size;

			result->x = -result->x;
			inputVector = *result;

			t.restart();
			return true;
		}
	return false;
}



