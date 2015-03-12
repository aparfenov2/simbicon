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




NOTES:    

This is research code, so it's not flawless or super user friendly.

This code was used to develop the controllers for the SIGGRAPH ASIA
paper: "Robust Task-based Control Policies for Physics-based Characters"
by Stelian Coros, Philippe Beaudoin, Michiel van de Panne.

To run this code you'll need Visual Studio 2008 (We've used 
the Express Edition version which is free). Once you open 
the solution file with VS, make sure the AppGUI project is 
set at the StartUp project. The code should then be easy 
to run.

Things to know:

- the file AppGUI/init/setup.tcl is used to control the size 
of the window. I've preset two size configurations, but they 
can be changed as needed.

- the file AppGUI/init/init.conF is used to load rigid bodies, 
characters and controllers. For now, only one character and one 
controller can be loaded at the same time - the program may 
crash otherwise. Check the file AppGUI/out/log.txt for an 
error message. If that doesn't work, you may have to run the 
code in DEBUG mode.

- the Push Interface checkbox is used to display an interface 
window on the left-top corner of the window. Click on it to 
throw balls at the character. The weight of the ball can be 
modified by changing the file data/objects/dodgeBall.rbs

- the CurveEditor checkbox brings in the controller editing 
interface - this isn't very user frinedly yet, but here are some
guidelines: the order of the editing windows is the same as
in the controller file 
(data/controllers/-some character-/-controller-.rbs
This is important, because each component controlls desired 
orientations about different axes. Click the "show target pose"
and manually change the Target pose phase slider to see the
result of the changes on the trajectory that is stracked by 
the controllers. Also, if a joint has a Strength component, 
it will always appear last.

- the Control Parameters window is used to select the state
and joint whose components are to be edited. This information
is all read from the controller file. If you wish to add a 
different component to the joint of a controller, do so
manually in the file, and then you can edit it using the
framework.

- Heading Control is used to make the character try to
keep facing the z-axis by applying appropriate torques
to the stance hip. Disable this if you want to make a turning 
controller, for instance.

- in the spline editing windows:
	- right mouse button can be used to change the scale/zoom in or out
	- left mouse shifts the spline up or down
	- SHIFT+left mouse add a control point
	- SHIFT+right mouse deletes a control point
	- left mouse button, on a control point moves it around
	- recommendations: make small changes, while the 
		simulation is running to see the effects
- Control Parameters
	- click the stick figure to save a checkpoint of the 
	active controller (this is saved in controlShots/*)
	- the left and right buttons can be used to navigate 
	between the different controller checkpoints

- main control window
	- << restarts the simulation: keeps all the changes made to the
	controller, but resets the simulation	
	- > starts simulations
	- || pause simulations
	- >| advance simulation by a tiny bit if paused
	- circular arrow thing: reloads controller and simulation 
	environment	(as per AppGUI/init/init.conF)
	- camera thing: start saving screenshots
	(saved in screenshots/)

-2D characters
	-planar characters can be simulated with this framework, and an
	example is given. The pelvis is constrained to stay on the y-z plane
	and only rotate about the x-axis (y == up, z == forward, x == lateral).
	Use the keyword "planar" in the descirption of the rigid body in the character
	rbs file (for instance data\characters\bip2D.rbs).

Credit for this code should be given to:
	Stelian Coros, Philippe Beaudoin, Michiel van de Panne
	from the University of British Columbia

