#include "dbproxy.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
DBProxy::DBProxy(QString user,QString passwd,QObject *parent) : QObject(parent)
{
    this->user = user;
    this->pass = passwd;
    try
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        ///Hard code for fast development
        db.setDatabaseName("res_db");
        db.setUserName(user);
        db.setPassword(passwd);
        bool ok = db.open();
        if(!ok)
        {
            qDebug() << "Open dababase failed!";
        }
    }
    catch(...)
    {
        qDebug() << "Catch exception when connect dababase!";
    }
}

DBProxy::DBProxy(QObject *parent )
{
    try
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setDatabaseName("res_db");
        //db.setHostName();
    }
    catch(...)
    {
        qDebug() << "Catch exception when connect dababase!";
    }
}

std::vector<Person> DBProxy::query(QueryInput& input) throw(MyException)
{
    std::vector<Person> result;
    QString sql= prepareSql(input);
    QSqlQuery query(db);
    try
    {
        bool res = query.exec(sql);
        if(res)
        {
            while (query.next())
            {
                Person person;
                int index=0;
                person.chinseName   = query.value(index++).toString();
                person.englisthName = query.value(index++).toString();
                person.gender       = query.value(index++).toString();
                person.label        = query.value(index++).toString();
                person.company      = query.value(index++).toString();
                person.orgnazation   = query.value(index++).toString();
                person.title         = query.value(index++).toString();
                person.mobile        = query.value(index++).toString();
                person.email         = query.value(index++).toString();
                person.location      = query.value(index++).toString();
                person.generalInfo   = query.value(index++).toString();
                person.timeStamp     = query.value(index++).toString();
                result.push_back(person);
            }
        }
        else
        {
           // throw new MyException("Query in database failed,return false!");
            qDebug()<< "Execute sql query failed!";
        }
    }
    catch(...)
    {
        throw new MyException("Query in database exception!");
    }
    return result;
}

static inline QString getSqlString(QString& str)
{
    return " '%" +  str + "%' ";
}

static QString getSqlSubString(std::pair<ATTRIBUTES_DEF,QString> pair)
{
    QString result;
    switch(pair.first)
    {
    case ATTR_CHINDES_NAME:
        result = " name LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_ENGLISH_NAME:
        result = " en_name LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_GENDER:
        result = " gender= "+ getSqlString(pair.second);
        break;
    case ATTR_LABEL:
        result = " label LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_COMPANY:
        result = " company LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_ORGNAZATION:
        result = " orgnazation LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_TITLE:
        result = " title LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_MOBILE:
        result = " mobile LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_EMAIL:
        result = " email LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_LOCATION:
        result = " location LIKE "+ getSqlString(pair.second);
        break;
    case ATTR_GENERAL_INFO:
        {
            QString keyword =  pair.second;
            QStringList keys = keyword.split(' ');
            for(int i=0;i < keys.size()-1;i++)
            {

                result += " generalInfo LIKE '%" + keys.at(i) +"%'  AND ";

            }
            if(false == keys.isEmpty())
            {
                result += " generalInfo LIKE '%" + keys.at(keys.size()-1) +"%' ";;
            }

            break;
        }
        //result = " generalInfo LIKE "+ getSqlString(pair.second);
        //break;
    case ATTR_TIME_STAMP:
        //result = " = "+ getSqlString(pair.second);
        break;
    default:

        break;
    }

    return result;
}
QString  DBProxy::prepareSql(QueryInput& input)
{
    QString sql("SELECT name,en_name,gender,label,company,orgnazation,title,mobile,email,location,generalInfo,timeStamp FROM basic_info WHERE  ");
    int index = 0;
    int size = input.size();
    for(auto it = input.begin();it != input.end();it++,index++)
    {
        sql += getSqlSubString(*it);
        //There is no AND at last query condition
        if(index <= size -2)
        {
            sql += " AND" ;
        }
    }
    sql +=" ORDER BY timeStamp DESC";
    qDebug()<<"Prepare to exectute sql: " + sql;
    return sql;
}

DBProxy::~DBProxy()
{
    db.close();
}

bool DBProxy::tryConnectDB(QString user,QString pass)
{
   if(false == db.isOpen())
   {
        bool result = db.open(user,pass);
        if(result)
        {
            this->user = user;
            this->pass = pass;
        }
        else
        {
            QSqlError error = db.lastError();
            qDebug() << "Connect DB failed with error:" << error.databaseText();
        }

        return result;
   }
   else
   {
       return 0==(this->user.compare(user) && this->pass.compare(pass));
   }
}
