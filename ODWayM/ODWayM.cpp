//====================================================================
//  ODWayM.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODMBase/ODDBHandle.h>
#include <ODWayM/ODMTime.h>
#include <ODWayM/ODMGnome.h>

#include "ODWayM.h"

struct ODWayM::Impl
{
    ODMBaseList _DBList;
};

ODWayM *ODWayM::Instance(const std::string &DBPath)
{
    static ODWayM * obj = new ODWayM;
    if (!DBPath.empty())
    {
        ODDBHandle::Instance()->Setup(DBPath);
    }
    return obj;
}

ODWayM::ODWayM()
    : _Impl(new Impl)
{
}

ODWayM::~ODWayM()
{
    delete _Impl;
    _Impl = NULL;
}

void ODWayM::ReadDB()
{
    _Impl->_DBList.clear();
    ODDBHandle::Instance()->Select<ODMTime>(_Impl->_DBList);
    ODDBHandle::Instance()->Select<ODMGnome>(_Impl->_DBList);
}

bool ODWayM::AddModel(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMBaseList tmpList;
    tmpList.push_back(ptr_);
    if (ODDBHandle::Instance()->Insert(tmpList))
    {
        Result = true;
        _Impl->_DBList.push_back(ptr_);
        std::sort(_Impl->_DBList.begin(), _Impl->_DBList.end(), [](ODMBasePtr x, ODMBasePtr y){
            return x->_id < y->_id;
        });
    }
    return Result;
}

void ODWayM::GetList(const std::string &type_, ODMBaseList &list)
{
    std::for_each(_Impl->_DBList.begin(), _Impl->_DBList.end(), [&list, type_](ODMBasePtr &x){
        if (x->_type == type_)
        {
            list.push_back(x);
        }
    });
}

bool ODWayM::DeleteModel(const std::string &type_, const int &id_)
{
    bool Result = false;
    IntList tmpList;
    tmpList.push_back(id_);
    if (type_ == "ODMTime")
    {
        Result = ODDBHandle::Instance()->Delete<ODMTime>(tmpList);
    }
    else if (type_ == "ODMGnome")
    {
        Result = ODDBHandle::Instance()->Delete<ODMGnome>(tmpList);
    }
    if (Result)
    {
        auto pos = std::find_if(_Impl->_DBList.begin(), _Impl->_DBList.end(), [id_, type_](ODMBasePtr &x){
            return x->_id == id_ && x->_type == type_;
        });
        if (pos != _Impl->_DBList.end())
        {
            _Impl->_DBList.erase(pos);
        }
    }
    return Result;
}
