#include "formqueryresult.h"
#include "ui_formqueryresult.h"
#include <QFont>
#include <QTableWidget>
#include <exception>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QDebug>
#include <QClipboard>
#include "common.h"
#include "dbdateacontroler.h"
#include <QDate>
#include "formattributeitemselection.h"
#include <algorithm>
#include <set>
FormQueryResult::FormQueryResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormQueryResult),mobileIcon(":/images/mobile.jpg"),emailIcon(":/images/email.jpg")
{
    ui->setupUi(this);
    initTableWidget(ui->resultsTable);
    DBDateaControler::getInstance()->setResultsView(this);
    currentMobile = nullptr;
    currentEmail = nullptr;
    itemsSetting = new FormAttributeItemSelection(this);
    itemsSetting->setVisible(false);
    connect(itemsSetting,SIGNAL(itemVisualblitySetting(ItemVisual)),this,SLOT(itemVisualblitySetting(ItemVisual)));
    //qDebug() << "FormQueryResult construcion";
}


const static int NUMBER_OF_COLUMNS =12;
void FormQueryResult::initTableWidget(QTableWidget* table_widget)
{

    table_widget->verticalHeader()->setVisible(true);
    table_widget->setColumnCount(NUMBER_OF_COLUMNS);
    table_widget->setRowCount(MAX_ROWS_IN_TABLE);
    table_widget->resizeColumnToContents (0);
    table_widget->setMouseTracking(true);


    QStringList header;
    header<<tr("姓名")<<tr("英文名")<<tr("性别")<<tr("标签") << tr("公司")<< tr("组织")<< tr("职位")<< tr("手机")<< tr("邮箱") << tr("所在地") << tr("背景概要")<< tr("更新时间");
    table_widget->setHorizontalHeaderLabels(header);

    //table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFont font = table_widget->horizontalHeader()->font();
    font.setBold(true);
    table_widget->horizontalHeader()->setFont(font);

    table_widget->setStyleSheet("selection-background-color:lightblue;");
    table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    table_widget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");

    table_widget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");

    for(int i=0; i < MAX_ROWS_IN_TABLE;i++)
    {
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *englisthName = new QTableWidgetItem();
        QTableWidgetItem *gender = new QTableWidgetItem();
        QTableWidgetItem *label = new QTableWidgetItem();
        QTableWidgetItem *company = new QTableWidgetItem();
        QTableWidgetItem *orgnazation = new QTableWidgetItem();
        QTableWidgetItem *title = new QTableWidgetItem();
        QTableWidgetItem *mobile = new QTableWidgetItem();
        QTableWidgetItem *email = new QTableWidgetItem();
        QTableWidgetItem *location = new QTableWidgetItem();
        QTableWidgetItem *generalInfo = new QTableWidgetItem();
        QTableWidgetItem *timeStamp = new QTableWidgetItem();

        int columnIndex = 0;
        table_widget->setItem(i, columnIndex++, name);
        table_widget->setItem(i, columnIndex++, englisthName);
        table_widget->setItem(i, columnIndex++, gender);
        table_widget->setItem(i, columnIndex++, label);
        table_widget->setItem(i, columnIndex++, company);
        table_widget->setItem(i, columnIndex++, orgnazation);
        table_widget->setItem(i, columnIndex++, title);
        table_widget->setItem(i, columnIndex++, mobile);
        table_widget->setItem(i, columnIndex++, email);
        table_widget->setItem(i, columnIndex++, location);
        table_widget->setItem(i, columnIndex++, generalInfo);
        table_widget->setItem(i, columnIndex++, timeStamp);

    }
}

//static QIcon mobileIcon(":/images/mobile.jpg");
//static QIcon emailIcon(":/images/email.jpg");
static void clearContentsOfTableWidget(QTableWidget* table)
{
    for(int i=0;i < table->rowCount();i++)
    {
        for(int j=0; j < NUMBER_OF_COLUMNS;j++)
        {
            QTableWidgetItem* item = table->item(i,j);
            item->setText("");
            item->setStatusTip("");
            item->setIcon(QIcon());
        }
    }
}

void FormQueryResult::clearResult()
{
    ui->resultsTable->clear();
}

void FormQueryResult::addPerson(std::vector<Person> persons)
{
    if(persons.size() > MAX_ROWS_IN_TABLE)
    {
        throw new std::bad_exception();//"Too many records received in FormQueryResult::addPerson"
    }
    //Clear all the contents
 //   std::sort(persons.begin(),persons.end(),[](const Person&a,const Person&b){return QDate::fromString(a.timeStamp, "yyyy-MM-dd") > QDate::fromString(b.timeStamp, "yyyy-MM-dd");});
    clearContentsOfTableWidget(ui->resultsTable);
    for(unsigned int i=0;i < persons.size();i++)
    {
        Person person= persons.at(i);
        int index=0;
        QTableWidget* table = ui->resultsTable;

        table->item(i,index++)->setText(person.chinseName);
        table->item(i,index++)->setText(person.englisthName);
        table->item(i,index++)->setText(person.gender);
        table->item(i,index++)->setText(person.label);
        table->item(i,index++)->setText(person.company);
        table->item(i,index++)->setText(person.orgnazation);
        table->item(i,index++)->setText(person.title);
        //mobile and email show in hints
        table->item(i,index++)->setText("");
        table->item(i,index -1 )->setIcon(mobileIcon);
        table->item(i,index -1 )->setStatusTip(person.mobile);
        table->item(i,index++)->setText("");
        table->item(i,index -1 )->setIcon(emailIcon);
        table->item(i,index -1 )->setStatusTip(person.email);
        table->item(i,index++)->setText(person.location);
        table->item(i,index++)->setText(person.generalInfo);
        table->item(i,index++)->setText(person.timeStamp);


    }
}

FormQueryResult::~FormQueryResult()
{
    delete ui;
}

void FormQueryResult::on_resultsTable_itemEntered(QTableWidgetItem *item)
{

}


void FormQueryResult::updateCurrentData(std::vector<Person> data)
{
    qDebug()<< "received results from DB with size=" << data.size();
    addPerson(data);
}

static const int COLUMN_MOBILE_INDEX=7;
static const int COLUMN_EMAIL_INDEX=8;
void FormQueryResult::on_resultsTable_cellClicked(int row, int column)
{
    QTableWidget * table = ui->resultsTable;
    auto updateText = [table,row,column] ( QTableWidgetItem** current) { if(*current){(*current)->setText(""); }
                                                                                   *current =    table->item(row,column);
                                                                                    QString value = table->item(row,column)->statusTip();
                                                                                    table->item(row,column)->setText(value);
                                                                                      };
    if(COLUMN_MOBILE_INDEX ==  column)
    {
        updateText(&currentMobile);
    }
    else if(COLUMN_EMAIL_INDEX == column)
    {
        updateText(&currentEmail);
    }
}

void FormQueryResult::on_resultsTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    int column =COLUMN_MOBILE_INDEX;
    QTableWidget * table = ui->resultsTable;
    auto updateText = [table,row,column] ( QTableWidgetItem** current) { if(*current){(*current)->setText(""); }
                                                                                   *current =    table->item(row,column);
                                                                                    QString value = table->item(row,column)->statusTip();
                                                                                    table->item(row,column)->setText(value);
                                                                                      };
   updateText(&currentMobile);

}

void FormQueryResult::itemVisualblitySetting(ItemVisual itemsVisual)
{
    for(unsigned int i= ATTR_CHINDES_NAME; i < ATTR_MAX;i++)
    {
        if(itemsVisual.end() == std::find(itemsVisual.begin(),itemsVisual.end(),i))
        {
            ui->resultsTable->setColumnHidden(i,true);
        }
        else
        {
            ui->resultsTable->setColumnHidden(i,false);
        }
    }
}

void FormQueryResult::on_pushButton_clicked()
{

}

void FormQueryResult::on_queryWndBtn_clicked()
{
    emit queryWindowControl();
}

void FormQueryResult::on_itemSetting_clicked()
{
    itemsSetting->setVisible(true);
}

void FormQueryResult::on_pasteBtn_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QList<QTableWidgetItem *> itemlist = ui->resultsTable->selectedItems();
    QString content;
    std::set<int> rows;
    for(auto item:itemlist)
    {
        int row = item->row();
        rows.insert(row);

    }
    for(auto row:rows)
    {
        QString line;
        for(int i=ATTR_CHINDES_NAME;i < ATTR_MAX;i++)
        {

            if(ui->resultsTable->isColumnHidden(i)){
                continue;
            }
            if(ATTR_MOBILE != i)
            {

                 line +=ui->resultsTable->item(row,i)->text()+"\t";
            }
            else
            {
                line +=ui->resultsTable->item(row,i)->statusTip()+"\t";
            }

        }
       line.replace(QString("\n"), QString(""));
       line +="\n";
       qDebug() << "line :" << line;
       content += line;
    }
    clipboard->setText(content);
}

void FormQueryResult::keyReleaseEvent(QKeyEvent * event)
{

}
