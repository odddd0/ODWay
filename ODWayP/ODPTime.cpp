
#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPTime.h"

#include <map>

struct ODPTime::Impl
{
    Impl()
        : _curDate(""){}

    void InClassify(const std::string classify_, const std::string kindFirst_, const std::string kindSecond_)
    {
        StringListPtr tmpStrListPtr;
        // classify
        if (ODVectorUtil::RefreshInsert<std::string>(_classifyList, classify_))
        {
            // classify first appearance
            tmpStrListPtr = std::make_shared<StringList>();
            tmpStrListPtr->push_back(kindFirst_);
            _kindFirstList[classify_] = tmpStrListPtr;

            tmpStrListPtr = std::make_shared<StringList>();
            tmpStrListPtr->push_back(kindSecond_);
            StringListPtrMap tmpStrListPtrMap;
            tmpStrListPtrMap[kindFirst_] = tmpStrListPtr;
            _kindSecondList[classify_] = tmpStrListPtrMap;
        }
        else
        {
            tmpStrListPtr = _kindFirstList[classify_];
            if (ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, kindFirst_))
            {
                tmpStrListPtr = std::make_shared<StringList>();
                tmpStrListPtr->push_back(kindSecond_);
                _kindSecondList[classify_][kindFirst_] = tmpStrListPtr;
            }
            else
            {
                tmpStrListPtr = _kindSecondList[classify_][kindFirst_];
                ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, kindSecond_);
            }
        }
    }

    void ExpandData()
    {
        _classifyList.clear();
        _kindFirstList.clear();
        _kindSecondList.clear();
        _expandData.clear();

        OneTipPtr oneTipPtr = NULL;
        OneDayPtr oneDayPtr = NULL;
        int lastTime = 0;
        ODMBaseList tmpList;
        ODMTimePtr cur;
        ODWayM::Instance()->GetList("ODMTime", tmpList);
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            cur = std::static_pointer_cast<ODMTime>(x);

            // classify
            InClassify(cur->_classify, cur->_kindFirst, cur->_kindSecond);

            oneTipPtr = std::make_shared<OneTip>();
            oneTipPtr->_time = cur->_id;
            oneTipPtr->_classify = cur->_classify;
            oneTipPtr->_kindFirst = cur->_kindFirst;
            oneTipPtr->_kindSecond = cur->_kindSecond;
            oneTipPtr->_content = cur->_content;

            if (cur->_offsetMinute != 0)
            {
                oneTipPtr->_durationSecond = cur->_offsetMinute * 60;
            }
            else if (lastTime != 0)
            {
                oneTipPtr->_durationSecond = cur->_id - lastTime;
            }
            else
            {
                oneTipPtr->_durationSecond = 0;
            }

            if (!ODTimeUtil::IsSameDay(lastTime, oneTipPtr->_time))
            {
                // new day
                oneDayPtr = std::make_shared<OneDay>();
                _curDate = ODTimeUtil::Timestamp2String(oneTipPtr->_time, "%y-%m-%d");
                _expandData._dateList.push_back(_curDate);
                _expandData._dayList[_curDate] = oneDayPtr;
            }
            oneDayPtr->_tipList.push_back(oneTipPtr);

            lastTime = cur->_id;

        });
    }

    void AppendData(const ODMTimePtr &curPtr)
    {
        if (_expandData._dateList.empty())
        {
            ExpandData();
        }
        else
        {
            // get last day's last tip
            OneDayPtr lastDayPtr = _expandData._dayList[_expandData._dateList[_expandData._dateList.size() - 1]];
            OneTipPtr lastTipPtr = lastDayPtr->_tipList[(lastDayPtr->_tipList.size() - 1)];
            if (curPtr->_id > lastTipPtr->_time)
            {
                InClassify(curPtr->_classify, curPtr->_kindFirst, curPtr->_kindSecond);
                OneTipPtr tmpPtr = std::make_shared<OneTip>();
                tmpPtr->_time = curPtr->_id;
                tmpPtr->_classify = curPtr->_classify;
                tmpPtr->_kindFirst = curPtr->_kindFirst;
                tmpPtr->_kindSecond = curPtr->_kindSecond;
                tmpPtr->_content = curPtr->_content;
                if (curPtr->_offsetMinute != 0)
                {
                    tmpPtr->_durationSecond = curPtr->_offsetMinute * 60;
                }
                else
                {
                    tmpPtr->_durationSecond = tmpPtr->_time - lastTipPtr->_time;
                }

                _curDate = ODTimeUtil::Timestamp2String(tmpPtr->_time, "%y-%m-%d");
                if (!ODTimeUtil::IsSameDay(tmpPtr->_time, lastTipPtr->_time))
                {
                    // new Day
                    lastDayPtr = std::make_shared<OneDay>();
                    _expandData._dateList.push_back(_curDate);
                    _expandData._dayList[_curDate] = lastDayPtr;
                }
                lastDayPtr->_tipList.push_back(tmpPtr);
            }
            else
            {
                ExpandData();
            }
        }
    }

    void DeleteData(const int &id_)
    {
        // todo, swift delete
        ExpandData();
        _curDate = ODTimeUtil::Timestamp2String(id_, "%y-%m-%d");
    }

    StringList _classifyList;
    StringListPtrMap _kindFirstList;
    std::map<std::string, StringListPtrMap> _kindSecondList;
    ODPTime::ExpandData _expandData;
    std::string _curDate;
    IntList _lastCurList;
};

ODPTime *ODPTime::Instance()
{
    static ODPTime * obj = new ODPTime;
    return obj;
}

bool ODPTime::AddTime(const ODMTimePtr &curPtr_)
{
    bool Result = false;
    if (ODWayM::Instance()->AddModel(curPtr_))
    {
        Result = true;
        _Impl->AppendData(curPtr_);
    }
    return Result;
}

bool ODPTime::FastIdle()
{
    ODMTimePtr tmpPtr = std::make_shared<ODMTime>();
    tmpPtr->_classify = "Idle";
    tmpPtr->_kindFirst = "Idle";
    tmpPtr->_kindSecond = "Idle";
    tmpPtr->_content = "Fast Idle";
    return AddTime(tmpPtr);
}

bool ODPTime::DelDurTime(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_lastCurList.size())
    {
        if (_Impl->_lastCurList[index_] >= 0)
        Result = ODWayM::Instance()->DeleteModel("ODMTime", _Impl->_lastCurList[index_]);
    }
    if (Result)
    {
        _Impl->DeleteData(_Impl->_lastCurList[index_]);
    }
    return Result;
}

ODPTime::ODPTime()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

ODPTime::~ODPTime()
{
    delete _Impl;
    _Impl = NULL;
}

void ODPTime::GetCurList(StringList &list)
{
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_lastCurList.clear();
        if (std::find(_Impl->_expandData._dateList.begin(), _Impl->_expandData._dateList.end(), _Impl->_curDate) ==
                _Impl->_expandData._dateList.end())
        {
            _Impl->_curDate = _Impl->_expandData._dateList[_Impl->_expandData._dateList.size() - 1];
        }
        std::string tmpStr;
        list.clear();
        list.push_back(_Impl->_curDate);
        _Impl->_lastCurList.push_back(-1);
        list.push_back("");
        _Impl->_lastCurList.push_back(-1);
        std::for_each(_Impl->_expandData._dayList[_Impl->_curDate]->_tipList.begin(), _Impl->_expandData._dayList[_Impl->_curDate]->_tipList.end(), [&](OneTipPtr &x){
            tmpStr = ODTimeUtil::Timestamp2String(x->_time - x->_durationSecond, "%H:%M") + "-";
            tmpStr += ODTimeUtil::Timestamp2String(x->_time, "%H:%M") + "(";
            tmpStr += ODTimeUtil::Duration2String(x->_durationSecond) + "): ";
            tmpStr += x->_classify + "_" + x->_kindFirst + "_" + x->_kindSecond;
            list.push_back(tmpStr);
            _Impl->_lastCurList.push_back(x->_time);
        });
    }
}

void ODPTime::PrevCur()
{
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != 0)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i - 1];
            break;
        }
    }
}

void ODPTime::NextCur()
{
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != _Impl->_expandData._dateList.size() - 1)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i + 1];
            break;
        }
    }
}

void ODPTime::GetClassifyList(StringList &list)
{
    list = _Impl->_classifyList;
}

void ODPTime::GetKindFirstList(StringList &list, const std::string &key_)
{
    if (key_.empty() && !_Impl->_classifyList.empty())
    {
        list = *(_Impl->_kindFirstList[_Impl->_classifyList[0]]);
    }
    else
    {
        list = *(_Impl->_kindFirstList[key_]);
    }
}

void ODPTime::GetKindSecondList(StringList &list, const std::string &classify_, const std::string &key_)
{
    list = *(_Impl->_kindSecondList[classify_][key_]);
    //    _Impl->_kindFirstList[classify_][""];
    //    list = *(_Impl->_kindSecondList[""]);
}
