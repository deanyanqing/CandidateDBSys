#ifndef FORMQUERYRESULT_H
#define FORMQUERYRESULT_H

#include <QWidget>
#include <vector>
#include <QIcon>
#include "queryresults.h"
class QTableWidgetItem;
namespace Ui {
class FormQueryResult;
}

class QTableWidget;
class FormAttributeItemSelection;
typedef std::vector<ATTRIBUTES_DEF> ItemVisual;
class FormQueryResult : public QWidget
{
    Q_OBJECT

public:
    explicit FormQueryResult(QWidget *parent = 0);
    ~FormQueryResult();

signals:
    void queryWindowControl();
public slots:
    void updateCurrentData(std::vector<Person>);
    void clearResult();

protected:
    void keyReleaseEvent(QKeyEvent *);
private slots:
    void on_resultsTable_itemEntered(QTableWidgetItem *item);

    void on_resultsTable_cellClicked(int row, int column);

    void on_resultsTable_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_queryWndBtn_clicked();

    void on_itemSetting_clicked();
    void itemVisualblitySetting(ItemVisual);
    void on_pasteBtn_clicked();

private:
    void initTableWidget(QTableWidget* table_widget);
    void addPerson(std::vector<Person> persons);

private:
    Ui::FormQueryResult *ui;
    const  QIcon mobileIcon;
    const  QIcon emailIcon;
    QTableWidgetItem* currentMobile;
    QTableWidgetItem* currentEmail;
    FormAttributeItemSelection* itemsSetting;
};

#endif // FORMQUERYRESULT_H
