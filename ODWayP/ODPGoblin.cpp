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
        OneGnomePtr tmpOneGnomePtr;
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            tmpGoblinCoinPtr = std::static_pointer_cast<ODMGoblinCoin>(x);

            // CKK
            _expandData._ckk->appendData(tmpGoblinCoinPtr->_classify, tmpGoblinCoinPtr->_kindFirst, tmpGoblinCoinPtr->_kindSecond);

            // Compute Gnome
            if (tmpOneGnomePtr = _expandData._gnomeMap[tmpGoblinCoinPtr->_goldFrom])
            {
                tmpOneGnomePtr->_balance -= tmpGoblinCoinPtr->_count;
            }
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
    if (Result)
    {
        if (_Impl->_expandData._gnomeMap[ptr_->_goldFrom])
        {
            _Impl->_expandData._gnomeMap[ptr_->_goldFrom]->_balance -= ptr_->_count;
        }
    }
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

void ODPGoblin::GetGnomeList(StringList &list_)
{
    list_.clear();
    OneGnomePtr cur;
    std::string tmpStr;
    std::for_each(_Impl->_expandData._goldFromList.cbegin(), _Impl->_expandData._goldFromList.cend(), [&](const std::string &x){
        cur = _Impl->_expandData._gnomeMap[x];
        tmpStr.clear();

        tmpStr = x + "\n";
        tmpStr += "Balance:  " + std::to_string(cur->_balance);
        if (cur->_balance)
        {
            tmpStr.insert(tmpStr.end() - 2, '.');
        }
        tmpStr += "\n";

        list_.push_back(tmpStr);
    });
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
    _gnomeMap.clear();
}
