
#include <ODWayP/ODPTime.h>

#include "ODVTime.h"

ODVTime::ODVTime(QObject *parent) : QObject(parent)
{
    updateList();
    updateClass();
}

QStringList ODVTime::curList() const
{
    return m_curList;
}

QStringList ODVTime::classifyList() const
{
    return m_classifyList;
}

QStringList ODVTime::kindFirstList() const
{
    return m_kindFirstList;
}

QStringList ODVTime::kindSecondList() const
{
    return m_kindSecondList;
}

bool ODVTime::addTime(
        const int &year_,
        const int &month_,
        const int &day_,
        const int &hour_,
        const int &minute_,
        const int &second_,
        const bool &customTime_,
        const QString &classify_,
        const QString &kindFirst_,
        const QString &kindSecond_,
        const QString &content_)
{
    bool Result = false;
    ODMTimePtr tmpPtr = std::make_shared<ODMTime>();
    tmpPtr->_classify = classify_.toStdString();
    tmpPtr->_kindFirst = kindFirst_.toStdString();
    tmpPtr->_kindSecond = kindSecond_.toStdString();
    tmpPtr->_content = content_.toStdString();
    if (customTime_)
    {
        struct tm tmpTm;
        tmpTm.tm_year = year_ - 1900;
        tmpTm.tm_mon = month_ - 1;
        tmpTm.tm_mday = day_;
        tmpTm.tm_hour = hour_;
        tmpTm.tm_min = minute_;
        tmpTm.tm_sec = second_;
        tmpTm.tm_isdst = 0;
        time_t lt = mktime(&tmpTm);
        tmpPtr->_id = lt;
    }
    Result = ODPTime::Instance()->AddTime(tmpPtr);
    if (Result)
    {
        updateList();
        updateClass();
    }
    return Result;
}

void ODVTime::setCurList(QStringList curList)
{
    if (m_curList == curList)
        return;

    m_curList = curList;
    emit curListChanged(m_curList);
}

void ODVTime::updateList()
{
    StringList tmpList;
    ODPTime::Instance()->GetCurList(tmpList);
    m_curList.clear();
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_curList.push_back(x.c_str());
    });
}

void ODVTime::updateClass()
{
    m_classifyList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetClassifyList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_classifyList.push_back(x.c_str());
    });
    if (!m_classifyList.empty())
    {
        updateKindFirst(m_classifyList[0]);
    }

    if (!m_kindFirstList.empty())
    {
        updateKindSecond(m_classifyList[0], m_kindFirstList[0]);
    }
}

void ODVTime::prevDay()
{
    ODPTime::Instance()->PrevCur();
}

void ODVTime::nextDay()
{
    ODPTime::Instance()->NextCur();
}

void ODVTime::updateKindFirst(QString classify_)
{
    m_kindFirstList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetKindFirstList(tmpList, classify_.toStdString());
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_kindFirstList.push_back(x.c_str());
    });
}

void ODVTime::updateKindSecond(QString classify_, QString kind_)
{
    m_kindSecondList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetKindSecondList(tmpList, classify_.toStdString(), kind_.toStdString());
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_kindSecondList.push_back(x.c_str());
    });
}

void ODVTime::setClassifyList(QStringList classifyList)
{
    if (m_classifyList == classifyList)
        return;

    m_classifyList = classifyList;
    emit classifyListChanged(m_classifyList);
}

void ODVTime::setKindFirstList(QStringList kindFirstList)
{
    if (m_kindFirstList == kindFirstList)
        return;

    m_kindFirstList = kindFirstList;
    emit kindFirstListChanged(m_kindFirstList);
}

void ODVTime::setKindSecondList(QStringList kindSecondList)
{
    if (m_kindSecondList == kindSecondList)
        return;

    m_kindSecondList = kindSecondList;
    emit kindSecondListChanged(m_kindSecondList);
}
