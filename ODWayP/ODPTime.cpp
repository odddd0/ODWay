
#include <ODWayM/ODMTime.h>
#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPTime.h"

#include <map>

struct ODPTime::Impl
{
    Impl()
        : _curDate(""){}

    void ExpandData()
    {
        OneTipPtr oneTipPtr = NULL;
        OneDayPtr oneDayPtr = NULL;
        int lastTime = 0;
        ODMBaseList tmpList;
        ODMTimePtr cur;
        std::string tmpStr;
        StringListPtr tmpStrListPtr;
        ODWayM::Instance()->GetList("ODMTime", tmpList);
        std::for_each(tmpList.begin(), tmpList.end(), [&](ODMBasePtr &x){
            cur = std::static_pointer_cast<ODMTime>(x);

            // classify
            if (ODVectorUtil::RefreshInsert<std::string>(_classifyList, cur->_classify))
            {
                // classify first appearance
                tmpStrListPtr = std::make_shared<StringList>();
                tmpStrListPtr->push_back(cur->_kindFirst);
                _kindFirstList[cur->_classify] = tmpStrListPtr;

                tmpStrListPtr = std::make_shared<StringList>();
                tmpStrListPtr->push_back(cur->_kindSecond);
                _kindSecondList[cur->_kindFirst] = tmpStrListPtr;
            }
            else
            {
                tmpStrListPtr = _kindFirstList[cur->_classify];
                if (ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, cur->_kindFirst))
                {
                    tmpStrListPtr = std::make_shared<StringList>();
                    tmpStrListPtr->push_back(cur->_kindSecond);
                    _kindSecondList[cur->_kindFirst] = tmpStrListPtr;
                }
                else
                {
                    tmpStrListPtr = _kindSecondList[cur->_kindFirst];
                    ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, cur->_kindSecond);
                }
            }

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

    StringList _classifyList;
    StringListPtrMap _kindFirstList;
    StringListPtrMap _kindSecondList;
    StringList _curList;
    ODPTime::ExpandData _expandData;
    std::string _curDate;
};

ODPTime *ODPTime::Instance()
{
    static ODPTime * obj = new ODPTime;
    return obj;
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
        if (std::find(_Impl->_expandData._dateList.begin(), _Impl->_expandData._dateList.end(), _Impl->_curDate) ==
                _Impl->_expandData._dateList.end())
        {
            _Impl->_curDate = _Impl->_expandData._dateList[_Impl->_expandData._dateList.size() - 1];
        }
        std::string tmpStr;
        list.clear();
        list.push_back(_Impl->_curDate);
        std::for_each(_Impl->_expandData._dayList[_Impl->_curDate]->_tipList.begin(), _Impl->_expandData._dayList[_Impl->_curDate]->_tipList.end(), [&](OneTipPtr &x){
            tmpStr = ODTimeUtil::Timestamp2String(x->_time - x->_durationSecond, "%H:%M") + "-";
            tmpStr += ODTimeUtil::Timestamp2String(x->_time, "%H:%M") + "(";
            tmpStr += ODTimeUtil::Duration2String(x->_durationSecond, "%0Hh%Mm") + "): ";
            tmpStr += x->_classify + "_" + x->_kindFirst + "_" + x->_kindSecond;
            list.push_back(tmpStr);
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
    list = *(_Impl->_kindFirstList[key_]);
}

void ODPTime::GetKindSecondList(StringList &list, const std::string &key_)
{
    list = *(_Impl->_kindSecondList[key_]);
}
