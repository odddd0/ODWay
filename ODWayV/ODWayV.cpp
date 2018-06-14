//====================================================================
//  ODWayV.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPTime.h>
#include <ODWayP/ODPGoblin.h>

#include "ODWayV.h"

ODWayV::ODWayV(QObject *parent) : QObject(parent)
{

}

QString ODWayV::getDescription(const QString &name_)
{
    QString Result = "_error_";
    std::string tmpStr = "_error_";
    if (name_ == "Time table")
    {
        ODPTime::Instance()->GetRunningTimeStr(tmpStr);
    }
    else if (name_ == "Goblin table")
    {
        ODPGoblin::Instance()->GetTotalDescription(tmpStr);
    }
    Result = QString::fromStdString(tmpStr);
    return Result;
}
