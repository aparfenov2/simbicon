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

//#include <TCL/tcl.h>
//#include <TCL/tk.h>

#include "Utils.h"


/**
 * Output the message to a file...
 */
void logPrint(char *format, ...){
    static char message[1024];
    va_list vl;

	va_start(vl, format);   
	vsprintf(message, format, vl);
	va_end(vl);

    static FILE *fp = fopen("out\\log.txt", "wt");

    fprintf(fp, "%s", message);
    fflush(fp);
}


/**
	Converts a list of strings to a unique TCL string list
	The string is allocated using Tcl_Alloc, so it should be managed by TCL from now on
	Pass true to "enQuote" to put extra quotes around the generated string
*/
//char* stringListToTclList( DynamicArray<const char*> stringList, bool enQuote ) {
//
//	uint storageSize = 1;  // For terminating null
//	if( enQuote ) storageSize = 3; // For "\""  and  "\"" and terminating null
//
//	for( uint i=0; i < stringList.size(); ++i )
//		storageSize += 3 + strlen( stringList[i] );  // For "{string} "
//
//	char* buffer = Tcl_Alloc( storageSize );
//	int bufferIdx = 0;
//	if( enQuote ) buffer[bufferIdx++] = '\"';
//	for( uint i=0; i < stringList.size(); ++i ) {
//		buffer[bufferIdx++] = '{';
//		strcpy( buffer+bufferIdx, stringList[i] );
//		bufferIdx += strlen(stringList[i]);
//		buffer[bufferIdx++] = '}';
//		buffer[bufferIdx++] = ' ';
//	}
//	if( enQuote ) buffer[bufferIdx++] = '\"';
//	buffer[bufferIdx++] = 0;
//
//	return buffer;
//
//}



