
#include <ODWayM/ODMTime.h>
#include <ODWayM/ODWayM.h>

#include "ODPTime.h"

struct ODPTime::Impl
{
    StringList _curList;
};

ODPTime *ODPTime::Instance()
{
    static ODPTime * obj = new ODPTime;
    return obj;
}

ODPTime::ODPTime()
    : _Impl(new Impl)
{
    _Impl->_curList.push_back("test01");
    _Impl->_curList.push_back("test02");
    _Impl->_curList.push_back("test03");
    _Impl->_curList.push_back("test04");
    _Impl->_curList.push_back("test05");
    _Impl->_curList.push_back("test06");
    _Impl->_curList.push_back("test07");
    _Impl->_curList.push_back("test08");
    _Impl->_curList.push_back("test09");
    _Impl->_curList.push_back("test10");
    _Impl->_curList.push_back("test11");
    _Impl->_curList.push_back("test12");
}

ODPTime::~ODPTime()
{
    delete _Impl;
    _Impl = NULL;
}

void ODPTime::GetCurList(StringList &list)
{
    list = _Impl->_curList;
}
