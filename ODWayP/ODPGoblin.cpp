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
        std::for_each(tmpList.cbegin(), tmpList.cend(), [&](const ODMBasePtr &x){
            _expandData.appendGnome(x);
        });

        // ODMGoblinCoin
        tmpList.clear();
        ODWayM::Instance()->GetList("ODMGoblinCoin", tmpList);
        std::for_each(tmpList.cbegin(), tmpList.cend(), [&](const ODMBasePtr &x){
            _expandData.appendCoin(x);
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

bool ODPGoblin::AddGoblin(const ODMBasePtr &ptr_)
{
    bool Result = true;
    if (ptr_->_type == "ODMGnome")
    {
        // gnome name exist?
        ODMGnomePtr tmpPtr = std::static_pointer_cast<ODMGnome>(ptr_);
        auto pos = std::find(_Impl->_expandData._goldFromList.begin(), _Impl->_expandData._goldFromList.end(), tmpPtr->_name);
        if (pos != _Impl->_expandData._goldFromList.end())
        {
            Result = false;
        }
    }
    if (Result)
    {
        if (ODWayM::Instance()->AddModel(ptr_))
        {
            if (ptr_->_type == "ODMGoblinCoin")
            {
                Result = _Impl->_expandData.appendCoin(ptr_);
            }
            else if (ptr_->_type == "ODMGnome")
            {
                Result = _Impl->_expandData.appendGnome(ptr_);
            }
        }
    }
    return Result;
}

void ODPGoblin::GetCKK(CKKPtr &ckk_)
{
    ckk_ = _Impl->_expandData._ckk;
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

bool ODPGoblin::ExpandData::appendGnome(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGnomePtr cur = std::static_pointer_cast<ODMGnome>(ptr_);
    if (cur)
    {
        Result = true;
        // Gnome
        if (ODVectorUtil::RefreshInsert<std::string>(_goldFromList, cur->_name))
        {
            // new gnome
            _gnomeMap[cur->_name] = std::make_shared<ODPGoblin::OneGnome>();
        }
    }
    return Result;
}

bool ODPGoblin::ExpandData::appendCoin(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGoblinCoinPtr cur = std::static_pointer_cast<ODMGoblinCoin>(ptr_);
    ODPGoblin::OneGnomePtr tmpOneGnomePtr = NULL;
    if (cur)
    {
        Result = true;
        // CKK
        _ckk->appendData(cur->_classify, cur->_kindFirst, cur->_kindSecond);

        // Compute Gnome
        // SimplePay
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay)
        {
            if (tmpOneGnomePtr = _gnomeMap[cur->_goldFrom])
            {
                tmpOneGnomePtr->_balance -= cur->_count;
            }
        }
        // NormalTransit
        else if (cur->_state == ODMGoblinCoin::GoblinState::NormalTransit)
        {
            if (tmpOneGnomePtr = _gnomeMap[cur->_goldFrom])
            {
                tmpOneGnomePtr->_balance -= cur->_count;
            }
            if (tmpOneGnomePtr = _gnomeMap[cur->_classify])
            {
                tmpOneGnomePtr->_balance += cur->_count;
            }
        }
    }
    return Result;
}
