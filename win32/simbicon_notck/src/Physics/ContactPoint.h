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
//#include <Physics/RigidBody.h>

class RigidBody;
/**
	This class is mainly a container for a Contact Point. It holds information such as the world coordinates of the contact point, 
	the normal at the contact, the rigid bodies that generated it, etc.
*/
class ContactPoint{
public:
	//this is the world coordinate of the origin of the contact force...
	Point3d cp;
	//this is the normal at the contact point
	Vector3d n;
	//and this is the penetration depth
	double d;
	//this is the first rigid body that participated in the contact
	RigidBody* rb1;
	//and this is the second...
	RigidBody* rb2;
	//and this is the force applied (with f being applied to rb1, and -f to rb2)
	Vector3d f;

	//provide a copy operator
	ContactPoint& operator = (const ContactPoint& other){
		this->cp = other.cp;
		this->f = other.f;
		this->n = other.n;
		this->d = other.d;
		this->rb1 = other.rb1;
		this->rb2 = other.rb2;
		return *this;
	}

	//provide a copy operator
	ContactPoint(const ContactPoint& other){
		this->cp = other.cp;
		this->f = other.f;
		this->n = other.n;
		this->d = other.d;
		this->rb1 = other.rb1;
		this->rb2 = other.rb2;
	}
	//and a default constructor
	ContactPoint(){
		rb1 = rb2 = NULL;
	}

};

