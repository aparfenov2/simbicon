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
#include <time.h>
#include <windows.h>
/*==================================================================================================================================================================*
 |	This is a simple timer class, that can be reset at any point, and can be used to get the ellapsed time since the last reset. In windows, it will be implemented |
 |  using the methods QueryPerformanceFrequency() and QueryPerformanceCounter(). In Linux, it can be implemented using the method gettimeofday(). The timeEllapsed  |
 |  method will return the time, in seconds but expressed as a double, since the timer was reset.                                                                   |
 *==================================================================================================================================================================*/

class Timer{
private:
	//this is the start time of the timer, in milliseconds.
	long long int startTime;
	//this is the frequency of the performance counter
	long long int frequency;
public:
	/**
		Default constructor - resets the timer for the first time.
	*/
	Timer();
	/**
		Default destructor - doesn't do much.
	*/
	~Timer();
	/**
		This method resets the starting time. All the time Ellapsed function calls will use the reset start time for their time evaluations.
	*/
	void restart();
	
	/**
		This method returns the number of seconds that has ellapsed since the timer was reset.
	*/
	double timeEllapsed();
};

