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
        tmpPtr->_id = _Impl->_expandData._goldFromList.size();
        if (pos != _Impl->_expandData._goldFromList.end())
        {
            Result = false;
        }
    }
    if (Result)
    {
        Result = false;
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

void ODPGoblin::GetCoinList(StringList &list_, const std::string &goldType_)
{
    list_.clear();
    _Impl->_expandData._lastCoinNum.clear();
    std::string tmpStr;
    bool dayIn = false;
    std::for_each(_Impl->_expandData._dateList.cbegin(), _Impl->_expandData._dateList.cend(), [&](const std::string &x){
        list_.push_back(x);
        _Impl->_expandData._lastCoinNum.push_back(-1);
        dayIn = false;
        std::for_each(_Impl->_expandData._coinList[x].cbegin(), _Impl->_expandData._coinList[x].cend(), [&](const OneGoblinCoinPtr &y){
            tmpStr.clear();
            if (y->_classify.empty())
            {
                // transit
                if (y->_goldFrom == goldType_ || y->_goldTo == goldType_ || goldType_.empty())
                {
                    tmpStr = y->_goldFrom + " -> " + y->_goldTo + " (" + std::to_string(y->_count);
                    if (y->_count)
                    {
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                    tmpStr += ")";
                    if (y->_tips)
                    {
                        tmpStr += " Tips: " + std::to_string(y->_tips);
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                }
            }
            else
            {
                if (y->_goldFrom == goldType_ || goldType_.empty())
                {
                    // revoke
                    if (y->_state != 0)
                    {
                        tmpStr += "xx: ";
                    }
                    tmpStr += y->_goldFrom + " (" + std::to_string(y->_count);
                    if (y->_count)
                    {
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                    tmpStr += "): " + y->_classify + "_" + y->_kindFirst + "_" + y->_kindSecond;
                }
            }
            if (!tmpStr.empty())
            {
                dayIn = true;
                _Impl->_expandData._lastCoinNum.push_back(y->_id);
                list_.push_back(tmpStr);
            }
        });
        if (!dayIn)
        {
            _Impl->_expandData._lastCoinNum.erase(_Impl->_expandData._lastCoinNum.end() - 1);
            list_.erase(list_.end() - 1);
        }
        else
        {
            _Impl->_expandData._lastCoinNum.push_back(-1);
            list_.push_back("");
        }
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

bool ODPGoblin::RevokeCoin(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastCoinNum.size() && _Impl->_expandData._lastCoinNum[index_] >= 0)
    {
        ODMBasePtr tmpPtr;
        ODWayM::Instance()->GetPtr("ODMGoblinCoin", _Impl->_expandData._lastCoinNum[index_], tmpPtr);
        if (tmpPtr)
        {
            std::static_pointer_cast<ODMGoblinCoin>(tmpPtr)->_state = ODMGoblinCoin::GoblinState::PayRevoke;
            Result = ODWayM::Instance()->UpdateModel(tmpPtr);
            if (Result)
            {
                _Impl->ExpandData();
            }
        }
    }
    return Result;
}

bool ODPGoblin::UpGnome(const int &index_)
{
    bool Result = false;
    if (index_ > 0 && index_ < _Impl->_expandData._lastGnomeNum.size())
    {
        int tmpId = _Impl->_expandData._lastGnomeNum[index_];
        if (tmpId)
        {
            std::string upStr = _Impl->_expandData._goldFromList[tmpId];
            std::string downStr = _Impl->_expandData._goldFromList[tmpId - 1];
            _Impl->_expandData._goldFromList.erase(_Impl->_expandData._goldFromList.begin() + tmpId);
            _Impl->_expandData._goldFromList.insert(_Impl->_expandData._goldFromList.begin() + tmpId - 1, upStr);

            Result = _Impl->_expandData.chgGnome(upStr, downStr);
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
    _Impl->_expandData._lastGnomeNum.clear();
    _Impl->_expandData._lastGnomeNum.push_back(-1);
    OneGnomePtr cur;
    std::string tmpStr;
    int totalLastBill = 0;
    int totalCurrentBill = 0;
    int totalBalance = 0;
    std::for_each(_Impl->_expandData._goldFromList.cbegin(), _Impl->_expandData._goldFromList.cend(), [&](const std::string &x){
        cur = _Impl->_expandData._gnomeMap[x];
        tmpStr.clear();

        tmpStr = x + "\n";
        // credit
        if (cur->_creditLimits)
        {
            if (x != "History")
            {
                totalLastBill += cur->_billList[1];
            }
            tmpStr += "LastBill:  " + std::to_string(cur->_billList[1]);
            if (cur->_billList[1])
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
            tmpStr += "(" + std::to_string(cur->_billDates) + ")\n";

            if (x != "History")
            {
                totalCurrentBill += cur->_billList[0];
            }
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
            if (x != "History")
            {
                totalBalance += cur->_balance;
            }
            tmpStr += "Balance:  " + std::to_string(cur->_balance);
            if (cur->_balance)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
        }

        tmpStr += "\n";
        list_.push_back(tmpStr);
        _Impl->_expandData._lastGnomeNum.push_back(cur->_id);
    });
    tmpStr = "Total\n";
    std::string tmpIntStr = "";
    _Impl->_expandData._totalDescription.clear();
    tmpStr += "LastBill:  ";
    tmpIntStr = std::to_string(totalLastBill);
    if (totalLastBill)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr + " / ";

    tmpStr += "\nCurrentBill:  ";
    tmpIntStr = std::to_string(totalCurrentBill);
    if (totalCurrentBill)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr + " / ";

    tmpStr += "\nBalance:  ";
    tmpIntStr = std::to_string(totalBalance);
    if (totalBalance)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr;

    tmpStr += "\n";
    list_.insert(list_.begin(), tmpStr);
}

void ODPGoblin::GetGnomeNameByIndex(const int &index_, std::string &name_)
{
    name_.clear();
    if (index_ > 0 && index_ < _Impl->_expandData._lastGnomeNum.size())
    {
        int tmpId = _Impl->_expandData._lastGnomeNum[index_];
        if (tmpId >= 0)
        {
            name_ = _Impl->_expandData._goldFromList[tmpId];
        }
    }
}

void ODPGoblin::GetTotalDescription(std::string &str_)
{
    if (_Impl->_expandData._totalDescription.empty())
    {
        StringList tmpList;
        GetGnomeList(tmpList);
    }
    str_ = _Impl->_expandData._totalDescription;
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
    _lastGnomeNum.clear();
    _totalDescription.clear();
}

bool ODPGoblin::ExpandData::appendGnome(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGnomePtr cur = std::static_pointer_cast<ODMGnome>(ptr_);
    if (cur)
    {
        Result = true;
        // Gnome
        if (_goldFromList.end() == std::find(_goldFromList.begin(), _goldFromList.end(), cur->_name))
        {
            // new gnome
            _goldFromList.push_back(cur->_name);
            _gnomeMap[cur->_name] = std::make_shared<ODPGoblin::OneGnome>();
            _gnomeMap[cur->_name]->_creditLimits = cur->_creditLimits;
            _gnomeMap[cur->_name]->_billDates = cur->_billDates;
            _gnomeMap[cur->_name]->_dueDay = cur->_dueDay;
            _gnomeMap[cur->_name]->_id = cur->_id;
        }
    }
    return Result;
}

bool ODPGoblin::ExpandData::chgGnome(const std::string &name1_, const std::string &name2_)
{
    bool Result = false;
    OneGnomePtr tmpPtr1 = _gnomeMap[name1_];
    OneGnomePtr tmpPtr2 = _gnomeMap[name2_];
    if (tmpPtr1 && tmpPtr2)
    {
        ODMBaseList tmpList;
        ODMGnomePtr gnomePtr1 = std::make_shared<ODMGnome>();
        ODMGnomePtr gnomePtr2 = std::make_shared<ODMGnome>();
        tmpList.push_back(gnomePtr1);
        tmpList.push_back(gnomePtr2);

        gnomePtr1->_preId = tmpPtr1->_id;
        gnomePtr1->_id = (tmpPtr1->_id + 122) * 12200;
        gnomePtr1->_name = name1_;
        gnomePtr1->_creditLimits = tmpPtr1->_creditLimits;
        gnomePtr1->_billDates = tmpPtr1->_billDates;
        gnomePtr1->_dueDay = tmpPtr1->_dueDay;

        gnomePtr2->_preId = tmpPtr2->_id;
        gnomePtr2->_id = (tmpPtr2->_id + 122) * 12200;
        gnomePtr2->_name = name2_;
        gnomePtr2->_creditLimits = tmpPtr2->_creditLimits;
        gnomePtr2->_billDates = tmpPtr2->_billDates;
        gnomePtr2->_dueDay = tmpPtr2->_dueDay;

        if (ODWayM::Instance()->UpdateModel(tmpList))
        {
            gnomePtr1->_preId = (tmpPtr1->_id + 122) * 12200;
            gnomePtr1->_id = tmpPtr2->_id;
            gnomePtr2->_preId = (tmpPtr2->_id + 122) * 12200;
            gnomePtr2->_id = tmpPtr1->_id;


            tmpPtr1->_id = gnomePtr1->_id;
            tmpPtr2->_id = gnomePtr2->_id;
            Result = ODWayM::Instance()->UpdateModel(tmpList);
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
    int tmpInt = 0;
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
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        while (gnome->_billList.size() <= tmpIndex)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex] += cur->_count;
                    }
                }
                gnome->_balance -= cur->_count;
            }
        }
        // NormalTransit
        else if (cur->_state == ODMGoblinCoin::GoblinState::NormalTransit)
        {
            // gold to
            if (gnome = _gnomeMap[cur->_classify])
            {
                if (gnome->_creditLimits)
                {
                    // repay credit
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        while (gnome->_billList.size() <= tmpIndex + 1)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex + 1] = gnome->_billList[tmpIndex + 1] - cur->_count;
                    }
                }
                gnome->_balance += cur->_count;
            }
            // gold from
            if (gnome = _gnomeMap[cur->_goldFrom])
            {
                if (!cur->_kindSecond.empty())
                {
                    tmpInt = std::stoi(cur->_kindSecond);
                }
                if (gnome->_creditLimits)
                {
                    // credit withdraw
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        while (gnome->_billList.size() <= tmpIndex)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex] = gnome->_billList[tmpIndex] + cur->_count + tmpInt;
                    }
                }
                gnome->_balance -= cur->_count + tmpInt;
            }
        }
        // revoke
        else if (cur->_state == ODMGoblinCoin::GoblinState::PayRevoke)
        {
            // do nothing
        }

        // add to coinList
        tmpCoinPtr = std::make_shared<OneGoblinCoin>();
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay ||
                cur->_state == ODMGoblinCoin::GoblinState::PayRevoke)
        {
            tmpCoinPtr->_classify = cur->_classify;
            tmpCoinPtr->_kindFirst = cur->_kindFirst;
            tmpCoinPtr->_kindSecond = cur->_kindSecond;
        }
        else
        {
            tmpCoinPtr->_goldTo = cur->_classify;
            if (!cur->_kindSecond.empty())
            {
                tmpCoinPtr->_tips = std::stoi(cur->_kindSecond);
            }
        }
        tmpCoinPtr->_state = static_cast<int>(cur->_state);
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
    _id = 0;
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

    _state = 0;

    _tips = 0;
    _count = 0;
}
