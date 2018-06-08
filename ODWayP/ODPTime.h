#ifndef ODPTIME_H
#define ODPTIME_H

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMTime.h>

typedef std::vector<std::pair<std::string, int>> SIMapList;

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
        void AddTip(const std::string &classify_,
                    const std::string &kindFirst_,
                    const std::string &kindSecond_,
                    const int &second_);
        bool ToString(StringList &strList_);
        bool ToString(const std::string &classify_, StringList &strList_);
        bool ToString(const std::string &classify_, const std::string &kindFirst_, StringList &strList_);
        bool ToString(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_, StringList &strList_);

        // __SUM__ is sum.
        std::map<std::string, int> _classifySum;
        std::map<std::string, std::map<std::string, int>> _kindFirstSum;
        std::map<std::string, std::map<std::string, std::map<std::string, int>>> _kindSecondSum;
    };
    typedef std::shared_ptr<DaySum> DaySumPtr;

    struct ExpandData
    {
        void clear();

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
    bool CalDurTime(const int &index1_, const int &index2_, std::string &str_);

public:
    void GetCurList(StringList &list);
    void GetCurSumList(
            std::vector<StringList> &classifyList_,
            std::vector<std::vector<StringList>> &kindFirstList_,
            std::vector<std::vector<std::vector<StringList>>> &kindSecondList_);
    std::string GetCurSum();
    void GetRunningTimeStr(std::string &str_);

public:
    bool PrevCur();
    bool FirstCur();
    bool NextCur();
    bool LastCur();

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
