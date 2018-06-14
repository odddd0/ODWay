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

Q_DECLARE_METATYPE(CKKPtr);

ODVGoblin::ODVGoblin(QObject *parent)
    : QObject(parent)
    , _curGnome("")
{
}

QVariant ODVGoblin::getCKK()
{
    CKKPtr tmpPtr;
    ODPGoblin::Instance()->GetCKK(tmpPtr);
    return QVariant::fromValue<CKKPtr>(tmpPtr);
}

QStringList ODVGoblin::getGoldFromList()
{
    QStringList Result;
    StringList tmpList;
    ODPGoblin::Instance()->GetGoldFromList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

bool ODVGoblin::addSimplePay(const int &year_,
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
                             const double &count_,
                             const QString &content_)
{
    bool Result = false;
    if (!goldFrom_.isEmpty() &&!classify_.isEmpty() &&!kindFirst_.isEmpty() &&!kindSecond_.isEmpty())
    {
        ODMGoblinCoinPtr tmpPtr = std::make_shared<ODMGoblinCoin>();
        tmpPtr->_goldFrom = goldFrom_.toStdString();
        tmpPtr->_classify = classify_.toStdString();
        tmpPtr->_kindFirst = kindFirst_.toStdString();
        tmpPtr->_kindSecond = kindSecond_.toStdString();
        tmpPtr->_count = std::stoi(std::to_string(count_ * 100));
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
        Result = ODPGoblin::Instance()->AddGoblin(tmpPtr);
        if (Result)
        {

        }
    }
    return Result;
}

bool ODVGoblin::addTransit(const int &year_,
                           const int &month_,
                           const int &day_,
                           const int &hour_,
                           const int &minute_,
                           const int &second_,
                           const bool &customTime_,
                           const QString &goldFrom_,
                           const QString &goldTo_,
                           const double &count_,
                           const double &tips_,
                           const QString &content_)
{
    bool Result = false;
    if (!goldFrom_.isEmpty() &&!goldTo_.isEmpty())
    {
        ODMGoblinCoinPtr tmpPtr = std::make_shared<ODMGoblinCoin>();
        tmpPtr->_state = ODMGoblinCoin::GoblinState::NormalTransit;
        tmpPtr->_goldFrom = goldFrom_.toStdString();
        tmpPtr->_classify = goldTo_.toStdString();
        tmpPtr->_count = std::stoi(std::to_string(count_ * 100));
        tmpPtr->_kindSecond = std::to_string(std::stoi(std::to_string(tips_ * 100)));
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
        Result = ODPGoblin::Instance()->AddGoblin(tmpPtr);
        if (Result)
        {

        }
    }
    return Result;
}

QStringList ODVGoblin::getCoinList()
{
    QStringList Result;
    StringList tmpList;
    ODPGoblin::Instance()->GetCoinList(tmpList, _curGnome);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

bool ODVGoblin::delCoin(const int &index_)
{
    return ODPGoblin::Instance()->DelCoin(index_);
}

bool ODVGoblin::revokeCoin(const int &index_)
{
    return ODPGoblin::Instance()->RevokeCoin(index_);
}

bool ODVGoblin::setEditCoin(const int &index_)
{
    return ODPGoblin::Instance()->SetEditCoin(index_);
}

bool ODVGoblin::saveEditCoin(const bool &revoke_, const int &year_, const int &month_, const int &day_, const int &hour_, const int &minute_, const int &second_, const double &countSecond_)
{
    return ODPGoblin::Instance()->SaveEditCoin(revoke_, year_, month_, day_, hour_, minute_, second_, std::stoi(std::to_string(countSecond_ * 100)));
}

QString ODVGoblin::getCurGnomeStr(const QString &defaultStr)
{
    QString Result = defaultStr;
    if (!_curGnome.empty())
    {
        Result = QString::fromStdString(_curGnome);
    }
    return Result;
}

void ODVGoblin::updateEditCoin()
{
    ODPGoblin::Instance()->GetEditCoinText(
                _editCoinStr, _revoke, _year, _month, _day, _hour, _minute, _second, _countSecond);
}

QString ODVGoblin::getEditCoinStrText()
{
    return QString::fromStdString(_editCoinStr);
}

bool ODVGoblin::getEditCoinStrRevoke()
{
    return _revoke;
}

int ODVGoblin::getEditCoinStrYear()
{
    return _year;
}

int ODVGoblin::getEditCoinStrMonth()
{
    return _month;
}

int ODVGoblin::getEditCoinStrDay()
{
    return _day;
}

int ODVGoblin::getEditCoinStrHour()
{
    return _hour;
}

int ODVGoblin::getEditCoinStrMinute()
{
    return _minute;
}

int ODVGoblin::getEditCoinStrSecond()
{
    return _second;
}

double ODVGoblin::getEditCoinStrCountSecond()
{
    std::string tmpStr = std::to_string(_countSecond);
    if (_countSecond)
    {
        tmpStr.insert(tmpStr.end() - 2, '.');
    }
    return std::stod(tmpStr);
}

QStringList ODVGoblin::getGnomeList()
{
    QStringList Result;
    StringList tmpList;
    ODPGoblin::Instance()->GetGnomeList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    Result.push_back("Add");
    return Result;
}

bool ODVGoblin::addGnome(const QString &name_, const int &CreditLimits_, const int &BillDates_, const int &DueDay_)
{
    bool Result = false;
    if (!name_.isEmpty())
    {
        ODMGnomePtr tmpPtr = std::make_shared<ODMGnome>();
        tmpPtr->_name = name_.toStdString();
        tmpPtr->_creditLimits = CreditLimits_ * 100;
        tmpPtr->_billDates = BillDates_;
        tmpPtr->_dueDay = DueDay_;

        Result = ODPGoblin::Instance()->AddGoblin(tmpPtr);
        if (Result)
        {

        }
    }
    return Result;
}

bool ODVGoblin::upGnome(const int &index_)
{
    return ODPGoblin::Instance()->UpGnome(index_);
}

void ODVGoblin::setGnomeIndex(const int &index_)
{
    ODPGoblin::Instance()->GetGnomeNameByIndex(index_, _curGnome);
}
