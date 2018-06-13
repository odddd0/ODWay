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

    void ExpandData()
    {
        ResetExpanddata();
        ODMBaseList tmpList;
        ODWayM::Instance()->GetList("ODMGoblinCoin", tmpList);
        ODMGoblinCoinPtr tmpPtr;
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            tmpPtr = std::static_pointer_cast<ODMGoblinCoin>(x);
            ODVectorUtil::RefreshInsert<std::string>(_expandData._goldFromList, tmpPtr->_goldFrom);
            _expandData._ckk->appendData(tmpPtr->_classify, tmpPtr->_kindFirst, tmpPtr->_kindSecond);
        });
    }

    void ResetExpanddata()
    {
        _expandData.clear();
    }

    ODPGoblin::ExpandData _expandData;
};

ODPGoblin *ODPGoblin::Instance()
{
    static ODPGoblin * obj = new ODPGoblin;
    return obj;
}

bool ODPGoblin::AddSimplePay(const ODMGoblinCoinPtr &ptr_)
{
    bool Result = false;
    Result = ODWayM::Instance()->AddModel(ptr_);
    return Result;
}

void ODPGoblin::GetCKK(CKKPtr &ckk_)
{
    ckk_ = _Impl->_expandData._ckk;
}

ODPGoblin::ODPGoblin()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

ODPGoblin::~ODPGoblin()
{
    delete _Impl;
    _Impl = NULL;
}

ODPGoblin::ExpandData::ExpandData()
{
    _ckk = std::make_shared<ODCKK>();
}

void ODPGoblin::ExpandData::clear()
{
    _goldFromList.clear();
    _ckk.reset();
    _ckk = std::make_shared<ODCKK>();
}
