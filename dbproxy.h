#ifndef DBPROXY_H
#define DBPROXY_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <map>
#include <vector>
#include "common.h"
typedef std::map<ATTRIBUTES_DEF,QString> QueryInput;

class DBProxy : public QObject
{
    Q_OBJECT
public:
    explicit DBProxy(QString user,QString passwd,QObject *parent = 0);
    explicit DBProxy(QObject *parent = 0);
    ~DBProxy();

    std::vector<Person> query(QueryInput&) throw(MyException);
    bool tryConnectDB(QString user,QString pass);
public slots:

private:
    QString prepareSql(QueryInput& );
private:
    QSqlDatabase db ;
    QString user;
    QString pass;
};

#endif // DBPROXY_H
