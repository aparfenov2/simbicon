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


/**
  * Used for any sub window that needs to be displayed in the OpenGL window
  */
class SubGLWindow {

protected:
	
	// Define the editor interface size
	int editorPosX;   // Relative to LEFT side of the window (in pixel)
	int editorPosY;   // Relative to TOP side of the window (in pixel)
	int editorSizeX;  // (in pixel)
	int editorSizeY;  // (in pixel)

	double minX; // The minimum X value of the viewport (in unit)
	double minY; // The minimum Y value of the viewport (in unit)
	double maxX; // The maximum X value of the viewport (in unit)
	double maxY; // The maximum Y value of the viewport (in unit)

private:

	// Used to save current viewport settings to restore state at the end
	int viewportSettings[4];

protected:

	/**
		Converts from the mouse X position to the viewport pixel position
	*/
	int mouseXToPixel( int mouseX );

	/**
		Converts from the mouse Y position to the viewport pixel position
	*/
	int mouseYToPixel( int mouseY );

	/**
		Converts from a viewport X position to a pixel position
	*/
	double viewportXToPixel( double x );

	/**
		Converts from a viewport Y position to a pixel position
	*/
	double viewportYToPixel( double y );

	/**
		Converts from a pixel vector X position to a viewport vector
	*/
	double pixelVecXToViewport( int vecX );

	/**
		Converts from a pixel X position to a viewport position
	*/
	double pixelXToViewport( int posX );

	/**
		Converts from a pixel vector Y position to a viewport vector
	*/
	double pixelVecYToViewport( int vecY );

	/**
		Converts from a pixel Y position to a viewport position
	*/
	double pixelYToViewport( int posY );


	/**
		What needs to be done before the subwindow is drawn into
	*/
	void preDraw();

	/**
		What needs to be done after the subwindow is drawn into
	*/
	void postDraw();



public:


	/**
		Default constructor
	*/
	SubGLWindow( int posX, int posY, int sizeX, int sizeY );


	virtual void draw() = 0;

};