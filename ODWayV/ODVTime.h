#ifndef ODVTIME_H
#define ODVTIME_H

#include <QObject>

class ODVTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString runningTimeStr READ runningTimeStr WRITE setRunningTimeStr NOTIFY runningTimeStrChanged)
    Q_PROPERTY(QStringList curList READ curList WRITE setCurList NOTIFY curListChanged)
    Q_PROPERTY(QStringList classifyList READ classifyList WRITE setClassifyList NOTIFY classifyListChanged)
    Q_PROPERTY(QStringList kindFirstList READ kindFirstList WRITE setKindFirstList NOTIFY kindFirstListChanged)
    Q_PROPERTY(QStringList kindSecondList READ kindSecondList WRITE setKindSecondList NOTIFY kindSecondListChanged)

public:
    explicit ODVTime(QObject *parent = nullptr);

    QStringList curList();
    QStringList classifyList() const;
    QStringList kindFirstList() const;
    QStringList kindSecondList() const;
    QString runningTimeStr();

signals:
    void curListChanged(QStringList curList);
    void classifyListChanged(QStringList classifyList);
    void kindFirstListChanged(QStringList kindFirstList);
    void kindSecondListChanged(QStringList kindSecondList);
    void runningTimeStrChanged(QString runningTimeStr);

public slots:
    void setCurList(QStringList curList);
    void setClassifyList(QStringList classifyList);
    void setKindFirstList(QStringList kindFirstList);
    void setKindSecondList(QStringList kindSecondList);
    void setRunningTimeStr(QString runningTimeStr);

public slots:
    bool addTime(
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const bool &customTime_,
            const QString &classify_,
            const QString &kindFirst_,
            const QString &kindSecond_,
            const QString &content_);
    bool delTime(const int &index_);

public slots:
    void updateList();
    bool fastIdle();
    bool prevDay();
    bool firstDay();
    bool nextDay();
    bool lastDay();

public slots:
    void updateClass();
    void updateKindFirst(QString classify_);
    void updateKindSecond(QString classify_, QString kind_);

private:
    QStringList m_curList;
    QStringList m_classifyList;
    QStringList m_kindFirstList;
    QStringList m_kindSecondList;
    QString m_runningTimeStr;
};

#endif // ODVTIME_H
