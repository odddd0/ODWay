
#include <ODWayP/ODPTime.h>

#include "ODVTime.h"

ODVTime::ODVTime(QObject *parent) : QObject(parent)
{
    updateList();
}

QStringList ODVTime::curList() const
{
    return m_curList;
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

void ODVTime::prevDay()
{
    ODPTime::Instance()->PrevCur();
}

void ODVTime::nextDay()
{
    ODPTime::Instance()->NextCur();
}
