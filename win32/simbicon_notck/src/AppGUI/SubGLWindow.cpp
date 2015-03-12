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

#include "SubGLWindow.h"

#include <Include/glHeaders.h>

/**
	Default constructor
*/
SubGLWindow::SubGLWindow( int posX, int posY, int sizeX, int sizeY ) {
	editorPosX = posX;
	editorPosY = posY;
	editorSizeX = sizeX;
	editorSizeY = sizeY;

	minX = 0;
	maxX = (double)sizeX/sizeY;
	minY = 0;
	maxY = 1;
}


// NOTE: Viewport origin is bottom-left of the viewport (for pixels, pos and val)
//       Mouse origin is top-left of the containing window

int SubGLWindow::mouseXToPixel( int mouseX ) {
	return mouseX - editorPosX;
}

/**
	Converts from the mouse Y position to the viewport pixel position
*/
int SubGLWindow::mouseYToPixel( int mouseY ) {
	return editorSizeY - (mouseY - editorPosY) - 1;
}


double SubGLWindow::viewportXToPixel( double x ) {
	return (x - minX) * (editorSizeX-1) / (maxX-minX);
}

double SubGLWindow::viewportYToPixel( double y ) {
	return (y - minY) * (editorSizeY-1) / (maxY-minY);
}

double SubGLWindow::pixelVecXToViewport( int vecX ) {
	return vecX*(maxX-minX) / (double)(editorSizeX-1);
}

double SubGLWindow::pixelXToViewport( int posX ) {
	return minX + pixelVecXToViewport(posX);
}

double SubGLWindow::pixelVecYToViewport( int vecY ) {
	return vecY*(maxY-minY) / (double)(editorSizeY-1);
}

double SubGLWindow::pixelYToViewport( int posY ) {
	return minY + pixelVecYToViewport( posY );
}



void SubGLWindow::preDraw() {

	// Save current viewport settings 
	glGetIntegerv(GL_VIEWPORT, viewportSettings);

	// We want to always draw the curve editor in the upper-left corner
	int actualPosY = viewportSettings[3]-editorSizeY-editorPosY;
	glViewport(editorPosX,actualPosY,editorSizeX,editorSizeY);
	glScissor(editorPosX,actualPosY,editorSizeX,editorSizeY);
	glEnable(GL_SCISSOR_TEST);


	// Save projection matrix and sets it to a simple orthogonal projection
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(minX, maxX, minY, maxY);
	
	// Save model-view matrix and sets it to identity
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Save the attributes and set them to basic values
	glPushAttrib(GL_ENABLE_BIT|GL_POINT_BIT|GL_LINE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Clear the colors to draw on a black background
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0,0,0);
	glBegin(GL_QUADS);
		glVertex2d(minX, minY);
		glVertex2d(maxX, minY);
		glVertex2d(maxX, maxY);
		glVertex2d(minX, maxY);
	glEnd();

}

/**
	What needs to be done after the subwindow is drawn into
*/
void SubGLWindow::postDraw() {
	
	glPopAttrib();
	glPopMatrix();
    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	// Restore viewport
    glViewport(viewportSettings[0], viewportSettings[1], viewportSettings[2], viewportSettings[3]);
	glDisable(GL_SCISSOR_TEST);
}