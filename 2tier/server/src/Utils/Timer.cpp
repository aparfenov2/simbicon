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

#include <Utils/Timer.h>
#include <time.h>
/**
	This constructor initializes a timer.
*/
Timer::Timer(){
	//first, get an idea of the frequency...
//	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), (DWORD_PTR)1);
//	QueryPerformanceFrequency((LARGE_INTEGER *)&this->frequency);
//	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	restart();
	
}

/**
	Default timer destructor - doesn't do much.
*/
Timer::~Timer(){
}


// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    long diffInNanos = end_time.tv_nsec - start_time.tv_nsec;
    return diffInNanos;
}

/**
	This method resets the starting time.
*/
void Timer::restart(){
//	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), (DWORD_PTR)1);
//	QueryPerformanceCounter((LARGE_INTEGER *)&this->startTime);
//	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	this->startTime = timer_start();
}

/**
	This method returns the number of milliseconds that has ellapsed since the timer was restarted.
*/
double Timer::timeEllapsed(){
	long tempTime;
	//force the thread to run on CPU 0 because the QPC method is buggy
//	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), (DWORD_PTR)1);
//	QueryPerformanceCounter((LARGE_INTEGER *)&tempTime);
//	//let it run wild and free again
//	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	tempTime = timer_end(this->startTime);
	return (double)tempTime / 1000000.0d;
}


