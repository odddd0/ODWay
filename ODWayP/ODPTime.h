#ifndef ODPTIME_H
#define ODPTIME_H

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMTime.h>

class ODPTime
{
    struct OneTip
    {
        int _time;
        int _durationSecond;
        std::string _classify;
        std::string _kindFirst;
        std::string _kindSecond;
        std::string _content;
    };
    typedef std::shared_ptr<OneTip> OneTipPtr;

    struct OneDay
    {
        std::vector<OneTipPtr> _tipList;
    };
    typedef std::shared_ptr<OneDay> OneDayPtr;

    struct DaySum
    {
        void AddTip(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_, const int &second_)
        {
            _kindSecondSum[classify_][kindFirst_][kindSecond_] += second_;
            _kindSecondSum[classify_][kindFirst_]["__SUM__"] += second_;
            _kindFirstSum[classify_][kindFirst_] += second_;
            _kindFirstSum[classify_]["__SUM__"] += second_;
            _classifySum[classify_] += second_;
            _classifySum["__SUM__"] += second_;
        }

        // __SUM__ is sum.
        std::map<std::string, int> _classifySum;
        std::map<std::string, std::map<std::string, int>> _kindFirstSum;
        std::map<std::string, std::map<std::string, std::map<std::string, int>>> _kindSecondSum;
    };
    typedef std::shared_ptr<DaySum> DaySumPtr;

    struct ExpandData
    {
        void clear()
        {
            _dateList.clear();
            _dayList.clear();
            _sumList.clear();
        }
        StringList _dateList;
        std::map<std::string, OneDayPtr> _dayList;
        std::map<std::string, DaySumPtr> _sumList;
    };
public:
    static ODPTime * Instance();

public:
    bool AddTime(const ODMTimePtr &curPtr_);
    bool FastIdle();

public:
    bool DelDurTime(const int &index_);

public:
    void GetCurList(StringList &list);
    void GetCurSumList(StringList &list, const std::string &token_ = "");
    void GetRunningTimeStr(std::string &str_);

public:
    void PrevCur();
    void FirstCur();
    void NextCur();
    void LastCur();

public:
    void GetClassifyList(StringList &list);
    void GetKindFirstList(StringList &list, const std::string &key_ = "");
    void GetKindSecondList(StringList &list, const std::string &classify_, const std::string &key_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPTime();
    ~ODPTime();
};

#endif // ODPTIME_H
