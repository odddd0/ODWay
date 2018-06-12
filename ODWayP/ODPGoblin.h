//====================================================================
//  ODPGoblin.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
#define _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMGoblin.h>

class ODPGoblin
{
public:
    static ODPGoblin * Instance();

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPGoblin();
    ~ODPGoblin();
};

#endif // _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
