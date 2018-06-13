//====================================================================
//  ODVGoblin.h
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_
#define _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_

#include <QObject>
#include <QVariant>
#include <ODUtil/ODCKK.h>

class ODVGoblin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant varCkk READ varCkk WRITE setVarCkk NOTIFY varCkkChanged)
public:
    explicit ODVGoblin(QObject *parent = nullptr);

public:
    QVariant varCkk() const;

signals:
    void varCkkChanged(QVariant varCkk);

public slots:
    void setVarCkk(QVariant varCkk);
    QVariant getCKK();

public slots:
    void updateGoblin();

private:
    QVariant m_varCkk;
};

#endif // _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_
