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
    struct ExpandData
    {
        StringList _dateList;
        std::map<std::string, OneDayPtr> _dayList;
    };
public:
    static ODPTime * Instance();

public:
    bool AddTime(const ODMTimePtr &curPtr_);

public:
    void GetCurList(StringList &list);

public:
    void PrevCur();
    void NextCur();

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
