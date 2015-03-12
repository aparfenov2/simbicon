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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MathLib/MathLib.h>
#include <MathLib/ThreeTuple.h>


#include <gsl/matrix/gsl_matrix.h>
#include <gsl/vector/gsl_vector.h>

#include <MathLib/Matrix.h>

#define VECTOR_AT(v, i) (*((v->data + (i * v->tda ))))


/*====================================================================================================================================================================*
 | This class will be used to represent matrices of arbitrary sizes (m rows by n columns) that have elements of type double. The underlying data strucutre used by    |
 | this class is gsl's (Gnu Scientific Library) matrix class. This class also makes use of the ATLAS implementation of BLAS for some operations such as matrix-matrix |
 | multiplication. This class is meant to improve performance, not necessarily ease of use.                                                                           |
 *====================================================================================================================================================================*/

class Vector : public Matrix{
public:
	/**
		constructor - creates an n row vector that is not initialized to any particular values
	*/
	Vector(int n);

	/**
		default constructor
	*/
	Vector();

	/**
		copy constructor - performs a deep copy of the matrix passed in as a parameter.
	*/
	Vector(const Vector& other);

	/**
		destructor.
	*/
	~Vector();

	/**
		copy operator - performs a deep copy of the Vector passed in as a parameter.
	*/
	Vector& operator=(const Vector &other);

	/**
		copy operator - performs a deep copy of the Vector passed in as a parameter.
	*/
	Vector& operator=(const Matrix &other);	

	/**
		this method performs a shallow copy of the Vector that is passed in as a parameter.
	*/
	void shallowCopy(const Matrix& other);

	/**
		this method performs a deep copy of the vector that is passed in as a paramerer.
	*/
	void deepCopy(const Matrix& other);

	/**
		This method sets the current vector to be equal to one of the products: A * b or A'*b.
		The value of transA indicates if A is transposed or not
	*/
	void setToProductOf(const Matrix& A, const Matrix& B, bool transA = false, bool transB = false);


	/**
		This method sets the current vector to be equal to one of the rows of A - shallow column only!
	*/
	void setToRow(const Matrix& A, int row, int start = 0, int howMany = -1);

	/**
		This method sets the current vector to be equal to one of the cols of A - shallow column only!
	*/
	void setToCol(const Matrix& A, int col, int start = 0, int howMany = -1);

	/**
		This method prints the contents of the matrix - testing purpose only.
	*/
	void printVector() const;

	/**
		This method returns a copy of the value of the matrix at (i,j)
	*/
	double get(int i) const;

	/**
		This method sets the value of the matrix at (i,j) to newVal.
	*/
	void set(int i, double newVal);

	/**
		Computes the 2-norm squared for the current vector.
	*/
	inline double normSquared(){
		int r = getRowCount();
		double result = 0;
		for (int i=0;i<r;i++){
			double n = MATRIX_AT(matrix, i, 0) ;
			result += n*n;
		}
		return result;
	}

};


void testVectorClass();