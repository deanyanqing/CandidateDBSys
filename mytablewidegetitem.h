#ifndef MYTABLEWIDEGETITEM_H
#define MYTABLEWIDEGETITEM_H

#include <QTableWidgetItem>

class MyTableWidegetItem : public QTableWidgetItem
{
public:
    MyTableWidegetItem(const QString & text, int type = UserType);
};

#endif // MYTABLEWIDEGETITEM_H
