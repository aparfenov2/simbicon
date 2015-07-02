// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include <Ice/Identity.ice>

module Simbice {

    struct ThreeTuple  {
        double x;
        double y;
        double z;
    };
    

    struct Quaternion  {
        double s;
        ThreeTuple v;
    };
    
    struct RBState {
        int id; // rigit body id
        ThreeTuple position;
        Quaternion orientation;
        ThreeTuple velocity;
        ThreeTuple angularVelocity;
    };
    
    struct JointState {
        int id;
        ThreeTuple torque;
    };
    
    struct ContactPoint {
        ThreeTuple cp;
        ThreeTuple n;
        double d;
        int rb1;
        int rb2;
        ThreeTuple f;
    };
    
    sequence<RBState> BodyStatesList;
    sequence<JointState> JointStatesList;
    sequence<ContactPoint> ContactPointsList;
    
    struct AllState {
        BodyStatesList bodyStates;
        JointStatesList jointStates;
        ContactPointsList contactPoints;
        double absoluteTime;
    };

    interface ClientCallback {
        void acceptNewState(AllState newState);
    };
    
    interface SimbiconServer {
        void addClient(Ice::Identity ident);
        void acceptClientState(AllState oldState, Ice::Identity ident);
    };

};

