#include "queryresults.h"
#include <mutex>
#include "common.h"

QueryResults::QueryResults(QObject *parent) :
    QObject(parent)
{
}

static std::mutex mutex;
QueryResults* QueryResults::getInstance()
{
    static QueryResults* instance = nullptr;

    if(nullptr == instance)
    {
        mutex.lock();
        if(nullptr == instance)
        {
            instance = new QueryResults(nullptr);
        }
        mutex.unlock();
    }
    return instance;
}

void QueryResults::addPersons(std::vector<Person>& persons)
{
    this->results = persons;
    std::vector<Person> show;
    for(unsigned int i=0;i < MAX_ROWS_IN_TABLE && i < persons.size();i++)
    {
        show.push_back(persons.at(i));
    }
    emit  updateCurrentData(show);
}

void QueryResults::addPerson(Person& )
{

}


void QueryResults::changeCurrentPage(int target)
{

    std::vector<Person> data;
    for(int i= (target-1)*MAX_ROWS_IN_TABLE,j=0;i < results.size() && j < MAX_ROWS_IN_TABLE;i++,j++)
    {
        data.push_back(results.at(i));
    }

    emit this->updateCurrentData(data);
}

int QueryResults::getNumberOfPages()
{
    int one = results.size()%MAX_ROWS_IN_TABLE > 0 ? 1 : 0;
    return results.size()/MAX_ROWS_IN_TABLE + one;
}


