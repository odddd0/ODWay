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

void ODPGoblin::GetCoinList(StringList &list_)
{
    list_.clear();
    std::string tmpStr;
    std::for_each(_Impl->_expandData._dateList.cbegin(), _Impl->_expandData._dateList.cend(), [&](const std::string &x){
        list_.push_back(x);
        _Impl->_expandData._lastCoinNum.push_back(-1);
        std::for_each(_Impl->_expandData._coinList[x].cbegin(), _Impl->_expandData._coinList[x].cend(), [&](const OneGoblinCoinPtr &y){
            tmpStr.clear();

            if (y->_classify.empty())
            {
                // transit
                tmpStr = y->_goldFrom + " -> " + y->_goldTo + " (" + std::to_string(y->_count);
                if (y->_count)
                {
                    tmpStr.insert(tmpStr.end() - 2, '.');
                }
                tmpStr += ")";
            }
            else
            {
                tmpStr = y->_goldFrom + " (" + std::to_string(y->_count);
                if (y->_count)
                {
                    tmpStr.insert(tmpStr.end() - 2, '.');
                }
                tmpStr += "): " + y->_classify + "_" + y->_kindFirst + "_" + y->_kindSecond;
            }
            _Impl->_expandData._lastCoinNum.push_back(y->_id);
            list_.push_back(tmpStr);
        });
        _Impl->_expandData._lastCoinNum.push_back(-1);
        list_.push_back("");
    });
}

bool ODPGoblin::DelCoin(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastCoinNum.size() && _Impl->_expandData._lastCoinNum[index_] >= 0)
    {
        Result = ODWayM::Instance()->DeleteModel("ODMGoblinCoin", _Impl->_expandData._lastCoinNum[index_]);
        if (Result)
        {
            _Impl->ExpandData();
        }
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
        // credit
        if (cur->_creditLimits)
        {
            tmpStr += "LastBill:  " + std::to_string(cur->_billList[1]);
            if (cur->_billList[1])
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
            tmpStr += "(" + std::to_string(cur->_billDates) + ")\n";

            tmpStr += "CurrentBill:  " + std::to_string(cur->_billList[0]);
            if (cur->_billList[0])
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
            tmpStr += "\nAvailableCredit:  " + std::to_string(cur->_creditLimits + cur->_balance);
            if (cur->_creditLimits + cur->_balance)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
        }
        else
        {
            tmpStr += "Balance:  " + std::to_string(cur->_balance);
            if (cur->_balance)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
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
    _coinList.clear();
    _dateList.clear();
    _lastCoinNum.clear();
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
            _gnomeMap[cur->_name]->_creditLimits = cur->_creditLimits;
            _gnomeMap[cur->_name]->_billDates = cur->_billDates;
            _gnomeMap[cur->_name]->_dueDay = cur->_dueDay;
        }
    }
    return Result;
}

bool ODPGoblin::ExpandData::appendCoin(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGoblinCoinPtr cur = std::static_pointer_cast<ODMGoblinCoin>(ptr_);
    OneGoblinCoinPtr tmpCoinPtr = NULL;
    int tmpIndex = -1;
    std::string tmpStr;
    ODPGoblin::OneGnomePtr gnome = NULL;
    if (cur)
    {
        Result = true;
        // CKK
        _ckk->appendData(cur->_classify, cur->_kindFirst, cur->_kindSecond);

        // Compute Gnome
        // Pay
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay)
        {
            if (gnome = _gnomeMap[cur->_goldFrom])
            {
                // CreditPay
                if (gnome->_creditLimits)
                {
                    if (ODTimeUtil::CalBillList(cur->_id, gnome->_billDates, tmpIndex, tmpStr) && tmpIndex >= 0)
                    {
                        while (gnome->_billList.size() <= tmpIndex)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex] += cur->_count;
                        gnome->_balance -= cur->_count;
                    }
                }
                // SimplePay
                else
                {
                    gnome->_balance -= cur->_count;
                }
            }
        }
        // NormalTransit
        else if (cur->_state == ODMGoblinCoin::GoblinState::NormalTransit)
        {
            if (gnome = _gnomeMap[cur->_classify])
            {
                if (gnome->_creditLimits)
                {
                    // repay credit
                    if (ODTimeUtil::CalBillList(cur->_id, gnome->_billDates, tmpIndex, tmpStr) && tmpIndex >= 0)
                    {
                        while (gnome->_billList.size() <= tmpIndex + 1)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex + 1] -= cur->_count;
                        gnome->_balance += cur->_count;
                    }
                }
                else
                {
                    gnome->_balance += cur->_count;
                }
            }
            if (gnome = _gnomeMap[cur->_goldFrom])
            {
                gnome->_balance -= cur->_count;
            }

        }

        tmpStr = "";
        // add to coinList
        tmpCoinPtr = std::make_shared<OneGoblinCoin>();
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay)
        {
            tmpCoinPtr->_classify = cur->_classify;
            tmpCoinPtr->_kindFirst = cur->_kindFirst;
            tmpCoinPtr->_kindSecond = cur->_kindSecond;
        }
        else
        {
            tmpCoinPtr->_goldTo = cur->_classify;
        }
        tmpCoinPtr->_goldFrom = cur->_goldFrom;
        tmpCoinPtr->_count = cur->_count;
        tmpCoinPtr->_content = cur->_content;
        tmpCoinPtr->_id = cur->_id;

        ODVectorUtil::RefreshInsert<std::string>(_dateList, ODTimeUtil::Timestamp2String(cur->_id, "%y-%m-%d"));
        _coinList[_dateList[0]].push_back(tmpCoinPtr);
    }
    return Result;
}

ODPGoblin::OneGnome::OneGnome()
{
    _balance = 0;
    _creditLimits = 0;
    _billDates = 1;
    _dueDay = 1;
    _billList.push_back(0);
    _billList.push_back(0);
}

ODPGoblin::OneGoblinCoin::OneGoblinCoin()
{
    _id = -1;
    _goldFrom = "";
    _goldTo = "";

    _classify = "";
    _kindFirst = "";
    _kindSecond = "";

    _content = "";

    _count = 0;
}
