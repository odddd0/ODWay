#ifndef ODVTIME_H
#define ODVTIME_H

#include <QObject>

class ODVTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList curList READ curList WRITE setCurList NOTIFY curListChanged)

public:
    explicit ODVTime(QObject *parent = nullptr);

    QStringList curList() const;

signals:
    void curListChanged(QStringList curList);

public slots:
    void setCurList(QStringList curList);
    void updateList();

private:
    QStringList m_curList;
};

#endif // ODVTIME_H
