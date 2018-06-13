//====================================================================
//  ODVGoblin.cpp
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPGoblin.h>

#include "ODVGoblin.h"

ODVGoblin::ODVGoblin(QObject *parent) : QObject(parent)
{
    updateGoblin();
}

QVariant ODVGoblin::varCkk() const
{
    return m_varCkk;
}

void ODVGoblin::setVarCkk(QVariant varCkk)
{
    if (m_varCkk == varCkk)
        return;

    m_varCkk = varCkk;
    emit varCkkChanged(m_varCkk);
}

QVariant ODVGoblin::getCKK()
{
    CKKPtr tmpPtr;
    ODPGoblin::Instance()->GetCKK(tmpPtr);
    return QVariant::fromValue<CKKPtr>(tmpPtr);
}

void ODVGoblin::updateGoblin()
{
    CKKPtr tmpPtr;
    ODPGoblin::Instance()->GetCKK(tmpPtr);
    m_varCkk = QVariant::fromValue<CKKPtr>(tmpPtr);
}
