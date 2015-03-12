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
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define DynamicArray std::vector
typedef unsigned int uint;


//define a prototype to a generic output function.
//int tprintf(const char *format, ...);
#define tprintf printf
//define a prototype to a generic output-to log file function.
void logPrint(char *format, ...);

/**
	This method throws an error with a specified text and arguments 
*/
inline void throwError(const char *fmt, ...){		// Custom error creation method

	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	throw text;
}


/**
	This method reads all the doubles from the given file and stores them in the array of doubles that is passed in
*/
inline void readDoublesFromFile(FILE* f, DynamicArray<double> *d){
	double temp;
	while (fscanf(f, "%lf\n", &temp) == 1)
		d->push_back(temp);
}


/**
	This method returns a pointer to the first non-white space character location in the provided buffer
*/
inline char* lTrim(char* buffer){
	while (*buffer==' ' || *buffer=='\t' || *buffer=='\n' || *buffer=='\r')
		buffer++;
	return buffer;
}

inline char* rTrim(char* buffer){
	int index = (int)strlen(buffer) - 1;
	while (index>=0){
		if (buffer[index]==' ' || buffer[index]=='\t' || buffer[index]=='\n' || buffer[index]=='\r'){
			buffer[index] = '\0';
			index--;
		}
		else
			break;
	}
	return buffer;
}

inline char* trim(char* buffer){
	return rTrim(lTrim(buffer));
}

/**
	This method reads a line from a file. It does not return empty lines or ones that start with a pound key - those are assumed to be comments.
	This method returns true if a line is read, false otherwise (for instance the end of file is met).
*/
inline bool readValidLine(char* line, FILE* fp){
	while (!feof(fp)){
		fgets(line, 100, fp);
		char* tmp = trim(line);
		if (tmp[0]!='#' && tmp[0]!='\0')
			return true;
	}

	return false;
}

/**
	This method returns a DynamicArray of char pointers that correspond to the addressed
	of the tokens that are separated by white space in the string that is passed in as a pointer.
*/
inline DynamicArray<char*> getTokens(char* input){
	DynamicArray<char*> result;
	input = lTrim(input);
	//read in the strings one by one - assume that each tokens are less than 100 chars in length
	while (input[0]!='\0'){
		result.push_back(input);
		char tempStr[100];
		sscanf(input, "%s", tempStr);
		input = lTrim(input + strlen(tempStr));
	}
	return result;
}


/**
	Converts a list of strings to a unique TCL string list
	The string is allocated using Tcl_Alloc, so it should be managed by TCL from now on
	Pass true to "enQuote" to put extra quotes around the generated string
*/
char* stringListToTclList( DynamicArray<const char*> stringList, bool enQuote = false );

#define __max__(x,y) (((x)>(y))?(x):(y))

