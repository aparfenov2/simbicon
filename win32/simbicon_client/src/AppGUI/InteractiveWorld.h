#pragma once

#include "application.h"
#include <Core/SimBiConFramework.h>
//#include <GLUtils/GLTexture.h>
//#include <AppGUI/InteractionInterface.h>

/**
  * This class is used to build ControllerFramework and use it to control articulated figures.
  */
class InteractiveWorld : public Application{
protected:
	//this is the physical world that contains all the objects inside
	AbstractRBEngine* world;

	//and this is the interaction interface that we will be using for throwing the dodgeball...
//	InteractionInterface* bInterface;

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
	 * This method gets called when the application gets initialized. 
	 */
	virtual void init();

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
