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

#include "CurveEditor.h"
#include "Globals.h"

#include <Include/glHeaders.h>

#define CAN_EDIT_POSITION
//#define CAN_EDIT_VIEW_POSITION

/**
	Default constructor
*/
CurveEditor::CurveEditor( int posX, int posY, int sizeX, int sizeY ) :
	SubGLWindow( posX, posY, sizeX, sizeY )
{
	minX = 0;
	maxX = 1;
	minY = -5;
	maxY = 5;
	trajectory = NULL;
	holdMouse = false;
	pointHeldIdx = -1;	
}

// NOTE: Viewport origin is bottom-left of the viewport (for pixels, pos and val)
//       Mouse origin is top-left of the containing window



/**
	Attaches a trajectory to be edited
	The CurveEditor doesn't own the trajectory and the caller is responsible for destroying
	the trajectory. If the trajectory is destroyed, the editor should be notified by passing "null"
*/
void CurveEditor::setTrajectory( Trajectory1D* trajectory ) {
	this->trajectory = trajectory;
}


/** 
	Draw the curve editor in the top-left corner of the OpenGL window
*/
void CurveEditor::draw() {

	SubGLWindow::preDraw();

	// Drow vertical ticks
	double vTickSize = pow( 10, floor(log10(maxX-minX)+0.5) - 1.0 );
	double vTickStart = ceil( minX/vTickSize ) * vTickSize;

	glColor3d(0.3,0.3,0.3);
	glLineWidth( 1.0f );
	glBegin( GL_LINES );
	for( double pos = vTickStart; pos <= maxX; pos += vTickSize ) {
		glVertex2d( pos, minY );
		glVertex2d( pos, maxY );
	}
	glEnd();

	// Draw horizontal ticks
	double hTickSize = pow( 10, floor(log10(maxY-minY)+0.5) - 1.0 );
	double hTickStart = ceil( minY/hTickSize ) * hTickSize;

	glColor3d(0.3,0.3,0.3);
	glLineWidth( 1.0f );
	glBegin( GL_LINES );
	for( double val = hTickStart; val <= maxY; val += hTickSize ) {
		glVertex2d( minX, val );
		glVertex2d( maxX, val );
	}
	glEnd();

	// Draw zeros
	glColor3d(0.5,0.5,0.5);
	glLineWidth( 2.0f );
	glBegin( GL_LINES );
	glVertex2d( 0, minY );
	glVertex2d( 0, maxY );
	glVertex2d( minX, 0 );
	glVertex2d( maxX, 0 );
	glEnd();

	// Print tick values
	glColor3d(1,1,1);
	double deltaPos = (maxX - minX) * 0.025;
	double deltaVal = (maxY - minY) * 0.025;
	int nbDigit = 0;
	if( vTickSize < 1 ) nbDigit = (int)((-log10(vTickSize))+0.5);
	for( double pos = vTickStart; pos <= maxX; pos += vTickSize ) {
		glRasterPos2d( pos - deltaPos, minY + deltaVal );
		gprintf( "%.*f", nbDigit, pos);
	}

	nbDigit = 0;
	if( hTickSize < 1 ) nbDigit = (int)((-log10(hTickSize))+0.5);
	for( double val = hTickStart; val <= maxY; val += hTickSize ) {
		glRasterPos2d( minX + deltaPos/2, val - deltaVal );
		gprintf( "%.*f", nbDigit, val );
	}


	if( trajectory && trajectory->getKnotCount() > 0 ) {
	
		// Draw the trajectory itself
		glColor3d(0.8,0.8,0.8);
		glLineWidth( 2.0f );
		glBegin( GL_LINE_STRIP );
		for( int i=0; i<editorSizeX; ++i ) {
			double pos = pixelXToViewport(i);
			double val = trajectory->evaluate_catmull_rom(pos);
			glVertex2d( pos, val );
		}
		glEnd();


		// Draw control points along the trajectory
		glPointSize( 8.0f );
		glBegin( GL_POINTS );
		for( int i=0; i<trajectory->getKnotCount(); ++i ) {
			if( pointHeldIdx == i ) glColor3d(1,1,0); else glColor3d(1,1,1);
			double pos = trajectory->getKnotPosition(i);
			double val = trajectory->getKnotValue(i);
			glVertex2d( pos, val );
		}
		glEnd();
	
	}

	// Draw the current time
	glColor3d(0.7,0.7,0);
	glLineWidth( 1.0f );
	glBegin( GL_LINES );
	glVertex2d( Globals::targetPosePhase, minY );
	glVertex2d( Globals::targetPosePhase, maxY );
	glEnd();


	// Draw a frame
	deltaPos = (maxX - minX) * 0.0001;
	deltaVal = (maxY - minY) * 0.0001;
	glLineWidth( 3.0f );
	glColor3d( 1, 1, 1 );
	glBegin( GL_LINE_LOOP );
	glVertex2d( minX+deltaPos, minY+deltaVal );
	glVertex2d( minX+deltaPos, maxY-deltaVal );
	glVertex2d( maxX-deltaPos, maxY-deltaVal );
	glVertex2d( maxX-deltaPos, minY+deltaVal );
	glEnd();


	// Restore attributes
	SubGLWindow::postDraw();


}

/**
	This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
	The coordinates are relative to top-left (OpenGL are usually relative to bot-left)
	Returns false if the event is not handled, true if it was handled
*/
bool CurveEditor::onMouseEvent(int eventType, int button, int mouseX, int mouseY) {

	int editorX = mouseXToPixel( mouseX );
	int editorY = mouseYToPixel( mouseY );

	// Can release mouse even if not in editor window
	if( eventType == MOUSE_UP ) {
		if( holdMouse ) {
			holdMouse = false;
			pointHeldIdx = -1;
			return true;
		}
		else 
			return false; // Mouse up not addressed to us. Not handled!
	}

	// Make sure the mouse is in the curve editor window
	if( editorX < 0 || editorX >= editorSizeX || editorY < 0 || editorY >= editorSizeY )
		return false;

	if( !holdMouse ) {
		if( eventType == MOUSE_DOWN ) {
			// Start holding a point, or the background
			if( button == MOUSE_RBUTTON ) {

				// If shift if pressed, delete a knot
				if( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) {
					if( !trajectory ) return false;
					int pointRemoved = -1;
					for( int i=0; i<trajectory->getKnotCount(); ++i ) {
						double distX = viewportXToPixel(trajectory->getKnotPosition(i)) - editorX;
						double distY = viewportYToPixel(trajectory->getKnotValue(i)) - editorY;
						if( distX*distX + distY*distY < 25.0 )
							pointRemoved = i;
					}
					if( pointRemoved == -1 ) return false;
					trajectory->removeKnot( pointRemoved );
					return true;
				}

				// Hold the background for resizing
				holdMouse = true;
				pointHeldIdx = -1;
				holdPosX = editorX;
				holdPosY = editorY;
			}
			else if( button == MOUSE_LBUTTON ) {
		
				// If shift if pressed, insert a knot
				if( glutGetModifiers() & GLUT_ACTIVE_SHIFT ) {
					if( !trajectory ) return false;
					trajectory->addKnot( pixelXToViewport( editorX ), pixelYToViewport( editorY ) );
					return true;
				}

				// By default, hold the background
				holdMouse = true;
				pointHeldIdx = -1;
				holdPosX = editorX;
				holdPosY = editorY;

				// But check if we are in the vicinity of a control point
				if( trajectory ) {
					for( int i=0; i<trajectory->getKnotCount(); ++i ) {
						double distX = viewportXToPixel(trajectory->getKnotPosition(i)) - editorX;
						double distY = viewportYToPixel(trajectory->getKnotValue(i)) - editorY;
						if( distX*distX + distY*distY < 25.0 )
							pointHeldIdx = i;
					}
				}

			}
		}
	}

	if( !holdMouse )
		// Still not holding anything? Not handled!
		return false;

	if( pointHeldIdx >= 0 ) {
		
		// Make sure we can manipulate the point
		if( !trajectory || pointHeldIdx >= trajectory->getKnotCount() || button != MOUSE_LBUTTON ) 
			return false;

		// Compute the new value
		double newVal = pixelYToViewport( editorY );

		trajectory->setKnotValue( pointHeldIdx, newVal );

#ifdef CAN_EDIT_POSITION

		// Compute the new position
		double newPos = pixelXToViewport( editorX );
	
		// Make sure new position is legal (> than previous knot, < than next knot, > 0)
		if( pointHeldIdx == 0 ) {
			if( newPos < 0 ) newPos = 0;
		}
		else {
			if( newPos <= trajectory->getKnotPosition(pointHeldIdx-1) ) 
				newPos = trajectory->getKnotPosition(pointHeldIdx-1) + 0.00001;
		}

		if( pointHeldIdx < trajectory->getKnotCount()-1 ) {
			if( newPos >= trajectory->getKnotPosition(pointHeldIdx+1) ) 
				newPos = trajectory->getKnotPosition(pointHeldIdx+1) - 0.00001;
		}

		trajectory->setKnotPosition( pointHeldIdx, newPos );

#endif

		return true;

	}
	else 
	{
		// Holding background

		if( button == MOUSE_LBUTTON ) {
			// Translate view						

			double deltaY = pixelVecYToViewport(holdPosY - editorY);
			minY += deltaY;
			maxY += deltaY;
			holdPosY = editorY;

#ifdef CAN_EDIT_VIEW_POSITION			
			double deltaX = pixelVecXToViewport(holdPosX - editorX);
			minX += deltaX;
			maxX += deltaX;
			holdPosX = editorX;

#endif

			return true;
		}

		if( button == MOUSE_RBUTTON ) {
			// Translate view
			
			double scaleY = (holdPosY - editorY)/(double)editorSizeY * 2.0f;
			if( scaleY >= 0 ) 
				scaleY = 1.0+scaleY;
			else
				scaleY = 1.0 / (1.0-scaleY);

			double midVal = (minY+maxY)/2.0;
			double sizeY = (maxY-minY)*scaleY;
			minY = midVal - sizeY/2.0;
			maxY = midVal + sizeY/2.0;
			holdPosY = editorY;
	
#ifdef CAN_EDIT_VIEW_POSITION			
			double scaleX = (holdPosX - editorX)/(double)editorSizeX * 2.0f;
			if( scaleX >= 0 ) 
				scaleX = 1.0+scaleX;
			else
				scaleX = 1.0 / (1.0-scaleX);

			double midPos = (minX+maxX)/2.0;
			double sizeX = (maxX-minX)*scaleX;
			minX = midPos - sizeX/2.0;
			maxX = midPos + sizeX/2.0;
			holdPosX = editorX;
#endif



		}

	}


	return false;

}
