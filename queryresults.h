#ifndef QUERYRESULTS_H
#define QUERYRESULTS_H

#include <QObject>
#include <QString>
#include "common.h"
#include <vector>

class QueryResults : public QObject
{
    Q_OBJECT
public:
    static QueryResults* getInstance();

    int getNumberOfPages();
    void changeCurrentPage(int target);

    void addPersons(std::vector<Person>& persons);

signals:
    void updateCurrentData(std::vector<Person>);

public slots:
    void addPerson(Person& person);


private:
    std::vector<Person> results;
    explicit QueryResults(QObject *parent = 0);
    QueryResults()=delete;
};

#endif // QUERYRESULTS_H
