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

        // ODMGnome
        tmpList.clear();
        ODWayM::Instance()->GetList("ODMGnome", tmpList);
        ODMGnomePtr tmpGnomePtr;
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            tmpGnomePtr = std::static_pointer_cast<ODMGnome>(x);

            // Gnome
            if (ODVectorUtil::RefreshInsert<std::string>(_expandData._goldFromList, tmpGnomePtr->_name))
            {
                // new gnome
                _expandData._gnomeMap[tmpGnomePtr->_name] = std::make_shared<ODPGoblin::OneGnome>();
            }
        });

        // ODMGoblinCoin
        tmpList.clear();
        ODWayM::Instance()->GetList("ODMGoblinCoin", tmpList);
        ODMGoblinCoinPtr tmpGoblinCoinPtr;
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            tmpGoblinCoinPtr = std::static_pointer_cast<ODMGoblinCoin>(x);

            // CKK
            _expandData._ckk->appendData(tmpGoblinCoinPtr->_classify, tmpGoblinCoinPtr->_kindFirst, tmpGoblinCoinPtr->_kindSecond);
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

bool ODPGoblin::AddGnome(const ODMBasePtr &ptr_)
{
    bool Result = false;
    if (ptr_->_type == "ODMGnome")
    {
        Result = ODWayM::Instance()->AddModel(ptr_);
    }
    return Result;
}

void ODPGoblin::GetGoldFromList(StringList &list_)
{
    list_ = _Impl->_expandData._goldFromList;
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
