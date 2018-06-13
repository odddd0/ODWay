//====================================================================
//  ODVGoblin.cpp
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPGoblin.h>
#include <ODWayM/ODMGoblinCoin.h>

#include "ODVGoblin.h"

Q_DECLARE_METATYPE(CKKPtr)

ODVGoblin::ODVGoblin(QObject *parent) : QObject(parent)
{
}

QVariant ODVGoblin::getCKK()
{
    CKKPtr tmpPtr;
    ODPGoblin::Instance()->GetCKK(tmpPtr);
    return QVariant::fromValue<CKKPtr>(tmpPtr);
}

bool ODVGoblin::addSimplePay(
        const int &year_,
        const int &month_,
        const int &day_,
        const int &hour_,
        const int &minute_,
        const int &second_,
        const bool &customTime_,
        const QString &goldFrom_,
        const QString &classify_,
        const QString &kindFirst_,
        const QString &kindSecond_,
        const int &count_,
        const QString &content_)
{
    bool Result = false;
    ODMGoblinCoinPtr tmpPtr = std::make_shared<ODMGoblinCoin>();
    tmpPtr->_goldFrom = goldFrom_.toStdString();
    tmpPtr->_classify = classify_.toStdString();
    tmpPtr->_kindFirst = kindFirst_.toStdString();
    tmpPtr->_kindSecond = kindSecond_.toStdString();
    tmpPtr->_count = count_;
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
    Result = ODPGoblin::Instance()->AddSimplePay(tmpPtr);
    if (Result)
    {

    }
    return Result;
}
