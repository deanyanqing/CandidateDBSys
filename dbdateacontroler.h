#ifndef DBDATEACONTROLER_H
#define DBDATEACONTROLER_H

#include <QObject>
#include "queryresults.h"
#include "formqueryresult.h"
#include "formjumptoolkit.h"
#include "common.h"
class DBProxy;
class DBDateaControler : public QObject
{
    Q_OBJECT
public:

    static DBDateaControler* getInstance();
    void nextPageHandler(int currentPage);
    void previousPageHandler(int currentPage);
    void homeHandler();
    void endHandler();
    void jumpToPage(unsigned int );

    inline void setResultsView(FormQueryResult* view){queryResults = view;connect(QueryResults::getInstance(),SIGNAL(updateCurrentData(std::vector<Person>)),view,SLOT(updateCurrentData(std::vector<Person>)));}
    inline void setToolkitView(FormJumpToolkit* view){toolkit = view;}
    inline bool isDBConnected(){return dbConnected;}
    void query(QueryInput& query);
signals:
    void connectDBSuccess(bool);
public slots:
    void loginVerify(QString name,QString password);
private:
    explicit DBDateaControler(QObject *parent = 0);
    void initDBProxy();
private:
    FormQueryResult* queryResults;
    FormJumpToolkit* toolkit;
    DBProxy* dbProxy;
    bool dbConnected;
};

#endif // DBDATEACONTROLER_H
