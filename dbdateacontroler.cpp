#include "dbdateacontroler.h"
#include "formjumptoolkit.h"
#include "formqueryresult.h"
#include "dbproxy.h"
#include <QDebug>
DBDateaControler::DBDateaControler(QObject *parent) :
    QObject(parent)
{
    dbProxy = nullptr;
    dbConnected = false;
}

const static int HOME_INDEX=1;
//NO thread-satety
DBDateaControler* DBDateaControler::getInstance()
{
    static DBDateaControler* instance= new DBDateaControler();
    return instance;
}

void DBDateaControler::nextPageHandler(int currentPage)
{
    if(QueryResults::getInstance()->getNumberOfPages() > currentPage)
    {
        QueryResults::getInstance()->changeCurrentPage(currentPage+1);
        toolkit->updatePageIndex(currentPage+1, QueryResults::getInstance()->getNumberOfPages());
    }
}


void DBDateaControler::jumpToPage(unsigned int page)
{
    if(page <QueryResults::getInstance()->getNumberOfPages()  )
    {
        toolkit->updatePageIndex(page, QueryResults::getInstance()->getNumberOfPages());
    }
}
void DBDateaControler::previousPageHandler(int currentPage)
{
    if(QueryResults::getInstance()->getNumberOfPages() >= currentPage && HOME_INDEX != currentPage)
    {
        QueryResults::getInstance()->changeCurrentPage(currentPage-1);
        toolkit->updatePageIndex(currentPage-1, QueryResults::getInstance()->getNumberOfPages());
    }
}

void DBDateaControler::homeHandler()
{
    QueryResults::getInstance()->changeCurrentPage(HOME_INDEX);
    toolkit->updatePageIndex(HOME_INDEX, QueryResults::getInstance()->getNumberOfPages());
}

void DBDateaControler::endHandler()
{
    QueryResults::getInstance()->changeCurrentPage(QueryResults::getInstance()->getNumberOfPages());
    toolkit->updatePageIndex(QueryResults::getInstance()->getNumberOfPages(), QueryResults::getInstance()->getNumberOfPages());

}


void DBDateaControler::initDBProxy()
{
    dbProxy = new DBProxy(this);
}

void DBDateaControler::query(QueryInput& query)
{
    if(dbProxy)
    {
        try
        {
        std::vector<Person> persons = dbProxy->query(query);
        QueryResults::getInstance()->addPersons(persons);
        toolkit->updatePageIndex(HOME_INDEX, QueryResults::getInstance()->getNumberOfPages());
        }
        catch(MyException& exception)
        {
            qDebug()<< "Catch excetpion " << exception.what() ;
        }


    }
}

void DBDateaControler::loginVerify(QString name,QString password)
{
    if(nullptr == dbProxy)
    {
        initDBProxy();
    }
    dbConnected = dbProxy->tryConnectDB(name,password);
    emit connectDBSuccess(dbConnected);
}
