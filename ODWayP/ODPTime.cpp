
#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPTime.h"

#include <map>

struct ODPTime::Impl
{
    Impl()
        : _curDate("")
        , _lastTip(NULL){}

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
        ResetExpandData();

        OneTipPtr oneTipPtr = NULL;
        OneDayPtr oneDayPtr = NULL;
        DaySumPtr oneSumPtr = NULL;
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
            else if (_lastTip)
            {
                oneTipPtr->_durationSecond = cur->_id - _lastTip->_time;
            }
            else
            {
                oneTipPtr->_durationSecond = 0;
            }

            if (_lastTip == NULL || !ODTimeUtil::IsSameDay(_lastTip->_time, oneTipPtr->_time))
            {
                // new day
                oneDayPtr = std::make_shared<OneDay>();
                oneSumPtr = std::make_shared<DaySum>();
                _curDate = ODTimeUtil::Timestamp2String(oneTipPtr->_time, "%y-%m-%d");
                _expandData._dateList.push_back(_curDate);
                _expandData._dayList[_curDate] = oneDayPtr;
                _expandData._sumList[_curDate] = oneSumPtr;
            }
            oneDayPtr->_tipList.push_back(oneTipPtr);

            _lastTip = oneTipPtr;

            oneSumPtr->AddTip(oneTipPtr->_classify, oneTipPtr->_kindFirst, oneTipPtr->_kindSecond, oneTipPtr->_durationSecond);
        });
    }

    void AppendData(const ODMTimePtr &curPtr)
    {
        if (_expandData._dateList.empty() || _lastTip == NULL)
        {
            ExpandData();
        }
        else
        {
            // get last day's last tip
            OneDayPtr lastDayPtr = _expandData._dayList[_expandData._dateList[_expandData._dateList.size() - 1]];
            DaySumPtr lastSumPtr = _expandData._sumList[_expandData._dateList[_expandData._dateList.size() - 1]];
            if (curPtr->_id > _lastTip->_time)
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
                    tmpPtr->_durationSecond = tmpPtr->_time - _lastTip->_time;
                }

                _curDate = ODTimeUtil::Timestamp2String(tmpPtr->_time, "%y-%m-%d");
                if (!ODTimeUtil::IsSameDay(tmpPtr->_time, _lastTip->_time))
                {
                    // new Day
                    lastDayPtr = std::make_shared<OneDay>();
                    lastSumPtr = std::make_shared<DaySum>();
                    _expandData._dateList.push_back(_curDate);
                    _expandData._dayList[_curDate] = lastDayPtr;
                    _expandData._sumList[_curDate] = lastSumPtr;
                }
                lastDayPtr->_tipList.push_back(tmpPtr);
                lastSumPtr->AddTip(tmpPtr->_classify, tmpPtr->_kindFirst, tmpPtr->_kindSecond, tmpPtr->_durationSecond);
                _lastTip = tmpPtr;
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

    void ResetExpandData()
    {
        _classifyList.clear();
        _kindFirstList.clear();
        _kindSecondList.clear();
        _expandData.clear();
        _curDate.clear();
        _lastCurList.clear();
        _lastTip = NULL;
    }

    StringList _classifyList;
    StringListPtrMap _kindFirstList;
    std::map<std::string, StringListPtrMap> _kindSecondList;
    ODPTime::ExpandData _expandData;
    std::string _curDate;
    std::vector<OneTipPtr> _lastCurList;
    OneTipPtr _lastTip;
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
        if (_Impl->_lastCurList[index_])
        {
            int tmpTime = _Impl->_lastCurList[index_]->_time;

            if (ODWayM::Instance()->DeleteModel("ODMTime", tmpTime))
            {
                _Impl->DeleteData(tmpTime);
                Result = true;
            }
        }
    }
    return Result;
}

bool ODPTime::CalDurTime(const int &index1_, const int &index2_, std::string &str_)
{
    bool Result = false;
    if (index1_ >= 0 && index1_ < _Impl->_lastCurList.size() &&
            index2_ >= 0 && index2_ < _Impl->_lastCurList.size())
    {
        OneTipPtr tip1 = _Impl->_lastCurList[index1_];
        OneTipPtr tip2 = _Impl->_lastCurList[index2_];
        OneTipPtr tmpTip;
        if (tip1 && tip2)
        {
            Result = true;
            if (tip1->_time < tip2->_time)
            {
                tmpTip = tip1;
                tip1 = tip2;
                tip2 = tmpTip;
            }
            str_ = ODTimeUtil::Duration2String(tip1->_time - tip2->_time + tip2->_durationSecond);
        }
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
        _Impl->_lastCurList.push_back(NULL);
        list.push_back("");
        _Impl->_lastCurList.push_back(NULL);
        std::for_each(_Impl->_expandData._dayList[_Impl->_curDate]->_tipList.begin(), _Impl->_expandData._dayList[_Impl->_curDate]->_tipList.end(), [&](OneTipPtr &x){
            tmpStr = ODTimeUtil::Timestamp2String(x->_time - x->_durationSecond, "%H:%M") + "-";
            tmpStr += ODTimeUtil::Timestamp2String(x->_time, "%H:%M") + "(";
            tmpStr += ODTimeUtil::Duration2String(x->_durationSecond) + "): ";
            tmpStr += x->_classify + "_" + x->_kindFirst + "_" + x->_kindSecond;
            list.push_back(tmpStr);
            _Impl->_lastCurList.push_back(x);
        });
    }
}

void ODPTime::GetCurSumList(std::vector<StringList> &classifyList_,
                            std::vector<std::vector<StringList> > &kindFirstList_,
                            std::vector<std::vector<std::vector<StringList> > > &kindSecondList_)
{
    if (!_Impl->_expandData._sumList.empty())
    {
        char tmpChar[20];
        DaySumPtr oneSum = _Impl->_expandData._sumList[_Impl->_curDate];
        std::string tmpStr = "";
        SIMapList listClassifySum, listKindFirstSum, listKindSecondSum;
        double tmpPercentage = 0;
        if (oneSum)
        {
            classifyList_.clear();
            kindFirstList_.clear();
            kindSecondList_.clear();

            std::for_each(oneSum->_classifySum.begin(), oneSum->_classifySum.end(), [&listClassifySum](const std::pair<std::string, int> &x){
                listClassifySum.push_back(x);
            });
            std::sort(listClassifySum.begin(), listClassifySum.end(), [](std::pair<std::string, int> &x, std::pair<std::string, int> &y){
                return x.second > y.second;
            });

            std::for_each(listClassifySum.begin(), listClassifySum.end(), [&](std::pair<std::string, int> &x){
                StringList metaClassify;
                std::vector<StringList> metaKindFirstClassify;
                std::vector<std::vector<StringList>> metaKindSecondClassify;
                if (oneSum->ToString(x.first, metaClassify))
                {
                    classifyList_.push_back(metaClassify);

                    listKindFirstSum.clear();
                    std::for_each(oneSum->_kindFirstSum[x.first].begin(), oneSum->_kindFirstSum[x.first].end(), [&listKindFirstSum](const std::pair<std::string, int> &x){
                        listKindFirstSum.push_back(x);
                    });
                    std::sort(listKindFirstSum.begin(), listKindFirstSum.end(), [](std::pair<std::string, int> &x, std::pair<std::string, int> &y){
                        return x.second > y.second;
                    });

                    std::for_each(listKindFirstSum.begin(), listKindFirstSum.end(), [&](std::pair<std::string, int> &y){
                        StringList tmpKindFirst;
                        if (oneSum->ToString(x.first, y.first, tmpKindFirst))
                        {
                            metaKindFirstClassify.push_back(tmpKindFirst);
                            std::vector<StringList> metaKindSecondKind;

                            listKindSecondSum.clear();
                            std::for_each(oneSum->_kindSecondSum[x.first][y.first].begin(), oneSum->_kindSecondSum[x.first][y.first].end(), [&listKindSecondSum](const std::pair<std::string, int> &x){
                                listKindSecondSum.push_back(x);
                            });
                            std::sort(listKindSecondSum.begin(), listKindSecondSum.end(), [](std::pair<std::string, int> &x, std::pair<std::string, int> &y){
                                return x.second > y.second;
                            });

                            std::for_each(listKindSecondSum.begin(), listKindSecondSum.end(), [&](std::pair<std::string, int> &z){
                                StringList tmpKindSecond;
                                if (oneSum->ToString(x.first, y.first, z.first, tmpKindSecond))
                                {
                                    metaKindSecondKind.push_back(tmpKindSecond);
                                }
                            });
                            metaKindSecondClassify.push_back(metaKindSecondKind);
                        }
                    });
                    kindFirstList_.push_back(metaKindFirstClassify);
                    kindSecondList_.push_back(metaKindSecondClassify);
                }
            });
        }
    }
}

std::string ODPTime::GetCurSum()
{
    std::string Result = "Sum";
    if (!_Impl->_expandData._sumList.empty())
    {
        DaySumPtr oneSum = _Impl->_expandData._sumList[_Impl->_curDate];
        if (oneSum)
        {
            StringList tmpList;
            oneSum->ToString(tmpList);
            Result = _Impl->_curDate + ": " + tmpList[1];
        }
    }
    return Result;
}

void ODPTime::GetRunningTimeStr(std::string &str_)
{
    if (_Impl->_lastTip)
    {
        time_t curTime = 0;
        int curTimestamp = time(&curTime);
        str_ = ODTimeUtil::Duration2String(curTimestamp - _Impl->_lastTip->_time, "__DIGITAL__");
    }
    else
    {
        str_ = "--:--:--";
    }
}

bool ODPTime::PrevCur()
{
    std::string tmpStr = _Impl->_curDate;
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != 0)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i - 1];
            break;
        }
    }
    return tmpStr != _Impl->_curDate;
}

bool ODPTime::FirstCur()
{
    std::string tmpStr = _Impl->_curDate;
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_curDate = _Impl->_expandData._dateList[0];
    }
    return tmpStr != _Impl->_curDate;
}

bool ODPTime::NextCur()
{
    std::string tmpStr = _Impl->_curDate;
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != _Impl->_expandData._dateList.size() - 1)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i + 1];
            break;
        }
    }
    return tmpStr != _Impl->_curDate;
}

bool ODPTime::LastCur()
{
    std::string tmpStr = _Impl->_curDate;
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_curDate = _Impl->_expandData._dateList[_Impl->_expandData._dateList.size() - 1];
    }
    return tmpStr != _Impl->_curDate;
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

void ODPTime::DaySum::AddTip(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_, const int &second_)
{
    _kindSecondSum[classify_][kindFirst_][kindSecond_] += second_;
    _kindSecondSum[classify_][kindFirst_]["__SUM__"] += second_;
    _kindFirstSum[classify_][kindFirst_] += second_;
    _kindFirstSum[classify_]["__SUM__"] += second_;
    _classifySum[classify_] += second_;
    _classifySum["__SUM__"] += second_;
}

bool ODPTime::DaySum::ToString(StringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty())
    {
        strList_.clear();
        strList_.push_back("_SUM_");
        strList_.push_back(ODTimeUtil::Duration2String(_classifySum["__SUM__"]));
        strList_.push_back(std::to_string(_classifySum["__SUM__"]));
        Result = true;
    }
    return Result;
}

bool ODPTime::DaySum::ToString(const std::string &classify_, StringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(classify_);

        tmpPercentage = (double)_classifySum[classify_] / (double)_classifySum["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(ODTimeUtil::Duration2String(_classifySum[classify_]) + " (" + tmpChar + "%)");
        strList_.push_back(std::to_string(_classifySum[classify_]));

        Result = true;
    }
    return Result;
}

bool ODPTime::DaySum::ToString(const std::string &classify_, const std::string &kindFirst_, StringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__" && kindFirst_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(kindFirst_);

        tmpPercentage = (double)_kindFirstSum[classify_][kindFirst_] / (double)_kindFirstSum[classify_]["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(ODTimeUtil::Duration2String(_kindFirstSum[classify_][kindFirst_]) + " (" + tmpChar + "%)");
        strList_.push_back(std::to_string(_kindFirstSum[classify_][kindFirst_]));

        Result = true;
    }
    return Result;
}

bool ODPTime::DaySum::ToString(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_, StringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__" && kindFirst_ != "__SUM__" && kindSecond_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(kindSecond_);

        tmpPercentage = (double)_kindSecondSum[classify_][kindFirst_][kindSecond_] / (double)_kindSecondSum[classify_][kindFirst_]["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(ODTimeUtil::Duration2String(_kindSecondSum[classify_][kindFirst_][kindSecond_]) + " (" + tmpChar + "%)");
        strList_.push_back(std::to_string(_kindSecondSum[classify_][kindFirst_][kindSecond_]));

        Result = true;
    }
    return Result;
}

void ODPTime::ExpandData::clear()
{
    _dateList.clear();
    _dayList.clear();
    _sumList.clear();
}
