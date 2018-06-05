#ifndef ODWAYM_H
#define ODWAYM_H

#include <ODMBase/ODMBase.h>

class ODWayM
{
public:
    static ODWayM *Instance(const std::string &DBPath = "");

public:
    void ReadDB();

public:
    void GetList(const std::string &type_, ODMBaseList &list);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODWayM();
    ~ODWayM();
};

#endif // ODWAYM_H
