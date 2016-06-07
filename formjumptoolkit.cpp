#include "formjumptoolkit.h"
#include "ui_formjumptoolkit.h"
#include "dbdateacontroler.h"
FormJumpToolkit::FormJumpToolkit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormJumpToolkit)
{
    ui->setupUi(this);
    currentPageIndex = 1;
    totalPages =1;
    DBDateaControler::getInstance()->setToolkitView(this);
}

FormJumpToolkit::~FormJumpToolkit()
{
    delete ui;
}

void FormJumpToolkit::on_textEdit_textChanged()
{

}

void FormJumpToolkit::on_homeBtn_clicked()
{
    DBDateaControler::getInstance()->homeHandler();
}

void FormJumpToolkit::on_previousBtn_clicked()
{
    DBDateaControler::getInstance()->previousPageHandler(currentPageIndex);
}

void FormJumpToolkit::on_nextBtn_clicked()
{
    DBDateaControler::getInstance()->nextPageHandler(currentPageIndex);
}

void FormJumpToolkit::on_endBtn_clicked()
{
    DBDateaControler::getInstance()->endHandler();
}


void FormJumpToolkit::updatePageIndex(int current,int total)
{
    this->currentPageIndex = current;
    this->totalPages = total;
    if(current == total)
    {
        ui->nextBtn->setEnabled(false);
    }
    else
    {
        ui->nextBtn->setEnabled(true);
    }

    ui->currentIndicator->setText(QString::number(current)+ " of " + QString::number(total));
    ui->jumpToInput->setText(QString::number(current));
}

void FormJumpToolkit::on_jumpToInput_textChanged(const QString &value)
{
    //int wantedPage = value.toInt();
    //DBDateaControler::getInstance()->jumpToPage(wantedPage);
}

void FormJumpToolkit::on_pushButton_clicked()
{
    if(false == ui->jumpToInput->text().isEmpty())
    {
        int wantedPage =  ui->jumpToInput->text().toInt();
        DBDateaControler::getInstance()->jumpToPage(wantedPage);
    }
}
