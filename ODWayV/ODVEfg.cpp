//====================================================================
//  ODVEfg.cpp
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPEfg.h>
#include <ODWayM/ODMEfg.h>

#include "ODVEfg.h"

ODVEfg::ODVEfg(QObject *parent)
    : QObject(parent)
{
}

QStringList ODVEfg::getEfgStrList()
{
    QStringList Result;
    StringList tmpList;
    ODPEfg::Instance()->GetEfgStrList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

void ODVEfg::markIndex(const int &index_)
{
    ODPEfg::Instance()->MarkIndex(index_);
}

