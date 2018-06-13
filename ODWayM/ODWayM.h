//====================================================================
//  ODWayM.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODWAYM_H_16EC2CC73F70B84A068EA4AB4E0606E4_
#define _ODWAYM_H_16EC2CC73F70B84A068EA4AB4E0606E4_

#include <ODMBase/ODMBase.h>

class ODWayM
{
public:
    static ODWayM *Instance(const std::string &DBPath = "");

public:
    void ReadDB();

public:
    bool AddModel(const ODMBasePtr &ptr_);

public:
    // only append
    void GetList(const std::string &type_, ODMBaseList &list);

public:
    bool DeleteModel(const std::string &type_, const int &id_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODWayM();
    ~ODWayM();
};

#endif // _ODWAYM_H_16EC2CC73F70B84A068EA4AB4E0606E4_
