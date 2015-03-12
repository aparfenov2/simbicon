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

#include "BalanceFeedback.h"
#include <Core/ConUtils.h>
#include <Physics/Joint.h>
#include <Core/SimBiController.h>


BalanceFeedback::BalanceFeedback(void){
}

BalanceFeedback::~BalanceFeedback(void){
}


void LinearBalanceFeedback::loadFromFile(FILE* f){
	if (f == NULL)
		throwError("File pointer is NULL - cannot read gain coefficients!!");

	//have a temporary buffer used to read the file line by line...
	char buffer[200];

	//this is where it happens.
	while (!feof(f)){
		//get a line from the file...
		fgets(buffer, 200, f);
		if (strlen(buffer)>195)
			throwError("The input file contains a line that is longer than ~200 characters - not allowed");
		char *line = lTrim(buffer);
		int lineType = getConLineType(line);
		switch (lineType) {
			case CON_FEEDBACK_END:
				//we're done...
				return;
				break;
			case CON_COMMENT:
				break;
			case CON_CV:
				if (sscanf(line, "%lf", &this->cv)!=1)
					throwError("A cv value must be specified!");
				break;
			case CON_CD:
				if (sscanf(line, "%lf", &this->cd)!=1)
					throwError("A cd value must be specified!");
				break;
			case CON_D_MIN:
				if (sscanf(line, "%lf", &this->dMin)!=1)
					throwError("A dMin value must be specified!");
				break;
			case CON_D_MAX:
				if (sscanf(line, "%lf", &this->dMax)!=1)
					throwError("A dMax value must be specified!");
				break;
			case CON_V_MIN:
				if (sscanf(line, "%lf", &this->vMin)!=1)
					throwError("A vMin value must be specified!");
				break;
			case CON_V_MAX:
				if (sscanf(line, "%lf", &this->vMax)!=1)
					throwError("A vMax value must be specified!");
				break;
			case CON_FEEDBACK_PROJECTION_AXIS:
				if (sscanf(line, "%lf %lf %lf", &this->feedbackProjectionAxis.x, &this->feedbackProjectionAxis.y, &this->feedbackProjectionAxis.z)!=3)
					throwError("The axis for a trajectory is specified by three parameters!");
				this->feedbackProjectionAxis.toUnit();
				break;
			case CON_NOT_IMPORTANT:
				tprintf("Ignoring input line: \'%s\'\n", line);
				break;
			default:
				throwError("Incorrect SIMBICON input file: \'%s\' - unexpected line.", buffer);
		}
	}
	throwError("Incorrect SIMBICON input file: No \'/jointTrajectory\' found ", buffer);
}


/**
	This method is used to write the state parameters to a file
*/
void LinearBalanceFeedback::writeToFile(FILE* f){
	if (f == NULL)
		return;

	fprintf( f, "\t\t\t%s linear\n", getConLineString(CON_FEEDBACK_START) );

	fprintf( f, "\t\t\t\t%s %lf %lf %lf\n", getConLineString(CON_FEEDBACK_PROJECTION_AXIS),
		feedbackProjectionAxis.x,
		feedbackProjectionAxis.y,
		feedbackProjectionAxis.z );
	fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_CD), cd );
	fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_CV), cv );
	if (dMin > -1000) fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_D_MIN), dMin);
	if (dMax < 1000) fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_D_MAX), dMax);
	if (vMin > -1000) fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_V_MIN), vMin);
	if (vMax < 1000) fprintf( f, "\t\t\t\t%s %lf\n", getConLineString(CON_V_MAX), vMax);


	fprintf( f, "\t\t\t%s\n", getConLineString(CON_FEEDBACK_END) );
}
