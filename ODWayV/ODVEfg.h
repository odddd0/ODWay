//====================================================================
//  ODVEfg.h
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVEFG_H_CCE32E355FBE6F23184040FB8936F230_
#define _ODVEFG_H_CCE32E355FBE6F23184040FB8936F230_

#include <QObject>
#include <QVariant>

class ODVEfg : public QObject
{
    Q_OBJECT

public:
    explicit ODVEfg(QObject *parent = nullptr);

public slots:
    QStringList getEfgStrList();
    bool markIndex(const int &index_);
    QString getProgressStr();
};

#endif // _ODVEFG_H_CCE32E355FBE6F23184040FB8936F230_
