#pragma once

#include "application.h"
#include <Core/SimBiConFramework.h>
#include <GLUtils/GLTexture.h>
#include <AppGUI/InteractionInterface.h>

/**
  * This class is used to build ControllerFramework and use it to control articulated figures.
  */
class InteractiveWorld : public Application{
protected:
	//this is the physical world that contains all the objects inside
	AbstractRBEngine* world;

	//and this is the interaction interface that we will be using for throwing the dodgeball...
	InteractionInterface* bInterface;

public:
	/**
	 * Constructor.
	 */
	InteractiveWorld(void);

	/**
	 * Destructor.
	 */
	virtual ~InteractiveWorld(void);

	/**
	 * This method is used to draw extra stuff on the screen (such as items that need to be on the screen at all times)
	 */
	virtual void drawExtras();

	/**
	 * This method gets called when the application gets initialized. 
	 */
	virtual void init();

	/**
     * This method is to be implemented by classes extending this one. The output of this function is a point that
	 * represents the world-coordinate position of the dodge ball, when the position in the throw interface is (x, y).
	 */
	virtual void getDodgeBallPosAndVel(double x, double y, double strength, Point3d* pos, Vector3d* vel) = 0;

	/**
	 * This method is to be implemented by classes extending this one. The output of this function is the velocity
	 * of the ball, in world coordinates, as a function of s, where s is the 'strength'
	 */

	/**
     *	This method is used when a mouse event gets generated. This method returns true if the message gets processed, false otherwise.
	 */
	virtual bool onMouseEvent(int eventType, int button, int mouseX, int mouseY);

	/**
	 * This method is called whenever the system wants to draw the current frame to an obj file
     * The file is already opened and the header is written, the application should only output
     * vertices and faces
	 *
	 * vertexIdxOffset indicates the index of the first vertex for this object, this makes it possible to render
	 * multiple different meshes to the same OBJ file
	 *
	 * Returns the number of vertices written to the file
     */
	uint renderToObjFile(FILE* fp, uint vertexIdxOffset);

};
