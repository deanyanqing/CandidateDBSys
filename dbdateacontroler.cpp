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

DBDateaControler* DBDateaControler::getInstance()
{
    //c++11 stardand:If control enters the declaration concurrently while the variable is being initialized,
    //  the concurrent execution shall wait for completion of the initialization.
    // Forget Double-check
    static DBDateaControler instance;
    return &instance;
}

DBDateaControler::~DBDateaControler()
{
    if(dbProxy)
    {
        delete dbProxy;
        dbProxy = nullptr;
    }
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
    //No consideration excetion case
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
