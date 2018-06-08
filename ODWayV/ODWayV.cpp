
#include <ODWayP/ODPTime.h>

#include "ODWayV.h"

ODWayV::ODWayV(QObject *parent) : QObject(parent)
{

}

QString ODWayV::getDescription(const QString &name_)
{
    QString Result = "_error_";
    std::string tmpStr = "";
    if (name_ == "Time table")
    {
        ODPTime::Instance()->GetRunningTimeStr(tmpStr);
        Result = QString::fromStdString(tmpStr);
    }
    return Result;
}
