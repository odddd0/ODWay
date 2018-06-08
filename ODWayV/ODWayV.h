#ifndef ODWAYV_H
#define ODWAYV_H

#include <QObject>

class ODWayV : public QObject
{
    Q_OBJECT

public:
    explicit ODWayV(QObject *parent = nullptr);

public slots:
    QString getDescription(const QString &name_);

private:
};

#endif // ODWAYV_H
