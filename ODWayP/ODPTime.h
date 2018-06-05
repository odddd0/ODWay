#ifndef ODPTIME_H
#define ODPTIME_H

#include <ODBase/ODBaseTypes.h>

class ODPTime
{
public:
    static ODPTime * Instance();

public:
    void GetCurList(StringList &list);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPTime();
    ~ODPTime();
};

#endif // ODPTIME_H
