//====================================================================
//  ODPGoblin.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPGoblin.h"

struct ODPGoblin::Impl
{
    Impl(){}
};

ODPGoblin *ODPGoblin::Instance()
{
    static ODPGoblin * obj = new ODPGoblin;
    return obj;
}

ODPGoblin::ODPGoblin()
    : _Impl(new Impl)
{
}

ODPGoblin::~ODPGoblin()
{
    delete _Impl;
    _Impl = NULL;
}
