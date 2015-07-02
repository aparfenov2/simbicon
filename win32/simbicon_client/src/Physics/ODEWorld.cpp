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

#include "ODEWorld.h"
#include <Utils/utils.h>
#include <Physics/Joint.h>
#include <Physics/HingeJoint.h>
#include <Physics/UniversalJoint.h>
#include <Physics/BallInSocketJoint.h>
#include <Core/SimGlobals.h>
#include <Utils/Timer.h>

#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>
#include <Simbice.h>


#define MAX_CONTACT_FEEDBACK 200



class ODEWorldImpl : public AbstractRBEngine {

public:
	Ice::CommunicatorPtr communicator;
	Simbice::SimbiconServerPrx server;
	Ice::Identity ident;

	bool newState_has;
	Simbice::AllState newState;
//	IceUtil::Mutex newStateMtx;
public:

	ODEWorldImpl();

	virtual ~ODEWorldImpl(void) {
		communicator->destroy();
	}

	virtual void advanceInTime(double deltaT);

	void acceptNewState(const Simbice::AllState &state) {
//		newStateMtx.lock();
		newState = state;
		newState_has = true;
//		newStateMtx.unlock();
	}

	void saveState(Simbice::AllState &state);

	void restoreState(const Simbice::AllState &state);


};


AbstractRBEngine * ODEWorldFactory::createODEWorld() {
	return new ODEWorldImpl();
}


class ClientCallbackImpl : public Simbice::ClientCallback {
public:
	ODEWorldImpl *world;
public:
	ClientCallbackImpl(ODEWorldImpl *_world) {
		world = _world;
	}

	virtual void acceptNewState(const ::Simbice::AllState& newState, const ::Ice::Current& ) override {
		world->acceptNewState(newState);
	}
};


ODEWorldImpl::ODEWorldImpl() {
	communicator = Ice::initialize();
	server = Simbice::SimbiconServerPrx::checkedCast(communicator->stringToProxy("simbice:tcp -h localhost -p 10000"));
	Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("");
    ident.name = IceUtil::generateUUID();
    ident.category = "";

    Simbice::ClientCallbackPtr cr = new ClientCallbackImpl(this);
    adapter->add(cr, ident);
    adapter->activate();
    server->ice_getConnection()->setAdapter(adapter);
	newState_has = false;
	server->addClient(ident);
}

void ODEWorldImpl::saveState(Simbice::AllState &state) {

// WAS COMMENTED
	//for (uint i=0;i<objects.size();i++) {

	//	RigidBody *rb = objects[i];
	//	if (rb->isLocked()) {
	//		continue;
	//	}

	//	Simbice::RBState rbs;
	//	rbs.id = i;
	//	rbs.position.x = rb->state.position.x;
	//	rbs.position.y = rb->state.position.y;
	//	rbs.position.z = rb->state.position.z;

	//	rbs.orientation.s = rb->state.orientation.s;
	//	rbs.orientation.v.x = rb->state.orientation.v.x;
	//	rbs.orientation.v.y = rb->state.orientation.v.y;
	//	rbs.orientation.v.z = rb->state.orientation.v.z;
	//	
	//	rbs.velocity.x = rb->state.velocity.x;
	//	rbs.velocity.y = rb->state.velocity.y;
	//	rbs.velocity.z = rb->state.velocity.z;

	//	rbs.angularVelocity.x = rb->state.angularVelocity.x;
	//	rbs.angularVelocity.y = rb->state.angularVelocity.y;
	//	rbs.angularVelocity.z = rb->state.angularVelocity.z;

	//	state.bodyStates.push_back(rbs);
	//}
// WAS COMMENTED ^^^



	// store torques

	for (uint j=0;j<jts.size();j++){
		Vector3d t = jts[j]->torque;

		Simbice::JointState js;
		js.id = j;
		js.torque.x = t.x;
		js.torque.y = t.y;
		js.torque.z = t.z;

		state.jointStates.push_back(js);

	}

}

void ODEWorldImpl::restoreState(const Simbice::AllState &state) {


	for (auto it = state.bodyStates.begin(); it != state.bodyStates.end(); it++) {

		Simbice::RBState rbs = *it;
		RigidBody *rb = objects[rbs.id];

		if (rb->isLocked()) {
			continue;
		}


		rb->state.position.x = rbs.position.x;
		rb->state.position.y = rbs.position.y;
		rb->state.position.z = rbs.position.z;

		rb->state.orientation.s = rbs.orientation.s;
		rb->state.orientation.v.x = rbs.orientation.v.x;
		rb->state.orientation.v.y = rbs.orientation.v.y;
		rb->state.orientation.v.z = rbs.orientation.v.z;
		
		rb->state.velocity.x = rbs.velocity.x;
		rb->state.velocity.y = rbs.velocity.y;
		rb->state.velocity.z = rbs.velocity.z;

		rb->state.angularVelocity.x = rbs.angularVelocity.x;
		rb->state.angularVelocity.y = rbs.angularVelocity.y;
		rb->state.angularVelocity.z = rbs.angularVelocity.z;

	}

	// read contactPoints
	contactPoints.clear();

	for (auto it = state.contactPoints.begin(); it != state.contactPoints.end(); it++) {

		ContactPoint cp;
		Simbice::ContactPoint scp = *it;
		cp.cp.x = scp.cp.x;
		cp.cp.y = scp.cp.y;
		cp.cp.z = scp.cp.z;

		cp.d = scp.d;

		cp.f.x = scp.f.x;
		cp.f.y = scp.f.y;
		cp.f.z = scp.f.z;

		cp.n.x = scp.n.x;
		cp.n.y = scp.n.y;
		cp.n.z = scp.n.z;

		cp.rb1 = objects[scp.rb1];
		cp.rb2 = objects[scp.rb2];

		contactPoints.push_back(cp);
	}

}


/**
	This method is used to integrate the forward simulation in time.
*/
void ODEWorldImpl::advanceInTime(double deltaT) {


	Simbice::AllState oldState;
	saveState(oldState);
	// send torques
	server->acceptClientState(oldState, ident);

	//while (!newState_has) {
	//	Sleep(1);
	//}

	if (newState_has) {

		Simbice::AllState tmp;
		tmp = newState;
		newState_has = false;

		restoreState(tmp);
	}

}

