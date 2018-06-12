//====================================================================
//  ODMGoblin.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMGoblin.h"

bool ODMGoblin::_init = true;

ODMGoblin::ODMGoblin()
    : ODMBase("ODMGoblin")
{
}

ODMGoblin::ODMGoblin(const StringList &stringList)
    : ODMBase("ODMGoblin")
{
    if (stringList.size() == 7)
    {
//        _preId = _id = std::stoi(stringList[0]);
//        _name = stringList[1];
//        _balance = std::stoi(stringList[2]);
//        _availableCreditLimits = std::stoi(stringList[3]);
//        _creditLimits = std::stoi(stringList[4]);
//        _billDates = std::stoi(stringList[5]);
//        _dueDay = std::stoi(stringList[6]);
    }
}

void ODMGoblin::GetSqlCreateTable(std::string &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'GnomeTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'Name' varchar(128),"
               "'Balance' integer DEFAULT(0),"
               "'AvailableCreditLimits' integer DEFAULT(0),"
               "'CreditLimits' integer DEFAULT(0),"
               "'BillDates' integer DEFAULT(0),"
               "'DueDay' integer DEFAULT(0));";
        _init = false;
    }
}

void ODMGoblin::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM GnomeTable";
}

void ODMGoblin::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM GnomeTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMGoblin::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
//    sql_ += "UPDATE GnomeTable SET "
//            "Id='" + std::to_string(_id) +
//            "',Name='" + _name +
//            "',Balance='" + std::to_string(_balance) +
//            "',AvailableCreditLimits='" + std::to_string(_availableCreditLimits) +
//            "',CreditLimits='" + std::to_string(_creditLimits) +
//            "',BillDates='" + std::to_string(_billDates) +
//            "',DueDay='" + std::to_string(_dueDay) +
//            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMGoblin::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
//    sql_ += "INSERT INTO GnomeTable VALUES('" +
//            std::to_string(_id) + "','" +
//            _name + "','" +
//            std::to_string(_balance) + "','" +
//            std::to_string(_availableCreditLimits) + "','" +
//            std::to_string(_creditLimits) + "','" +
//            std::to_string(_billDates) + "','" +
//            std::to_string(_dueDay) + "');";
}
