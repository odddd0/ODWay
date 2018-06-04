#ifndef ODMTIME_H
#define ODMTIME_H

#include <ODBase/ODMBase.h>

struct ODMTime : public ODMBase
{
public:
    ODMTime();
    ODMTime(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    int _offsetMinute;
    std::string _classify;
    std::string _kindFirst;
    std::string _kindSecond;
    std::string _content;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMTime> ODMTimePtr;

#endif // ODMTIME_H
