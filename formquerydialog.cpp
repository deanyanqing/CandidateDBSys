#include "formquerydialog.h"
#include "ui_formquerydialog.h"
#include "dbdateacontroler.h"
FormQueryDialog::FormQueryDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormQueryDialog)
{
    ui->setupUi(this);
}

FormQueryDialog::~FormQueryDialog()
{
    delete ui;
}

void FormQueryDialog::queryWindowControl()
{
    bool visible = this->isVisible();
    this->setVisible(!visible);
}

typedef std::map<ATTRIBUTES_DEF,QString> QueryInput;
void FormQueryDialog::on_queryBtn_clicked()
{
    if(false == DBDateaControler::getInstance()->isDBConnected())
    {

        emit notLogin();
        return;
    }

    bool allEmpty = true;
    QueryInput queryInput;
    if(false == ui->companyInput->text().isEmpty())
    {
        queryInput[ATTR_COMPANY]=ui->companyInput->text();
        allEmpty= false;
    }
    if(false == ui->emailInput->text().isEmpty())
    {
        queryInput[ATTR_EMAIL]=ui->emailInput->text();
        allEmpty= false;
    }
    if(false == ui->keyworkInput->text().isEmpty())
    {
        queryInput[ATTR_GENERAL_INFO]=ui->keyworkInput->text();
        allEmpty= false;
    }
    if(false == ui->locationInput->text().isEmpty())
    {
        queryInput[ATTR_LOCATION]=ui->locationInput->text();
        allEmpty= false;
    }
    if(false == ui->mobileInput->text().isEmpty())
    {
        queryInput[ATTR_MOBILE]=ui->mobileInput->text();
        allEmpty= false;
    }
    if(false == ui->nameInput->text().isEmpty())
    {
        queryInput[ATTR_CHINDES_NAME]=ui->nameInput->text();
        allEmpty= false;
    }
    if(false == ui->orgInput->text().isEmpty())
    {
        queryInput[ATTR_ORGNAZATION]=ui->orgInput->text();
        allEmpty= false;
    }
    if(false == ui->titleInput->text().isEmpty())
    {
        queryInput[ATTR_TITLE]=ui->titleInput->text();
        allEmpty= false;
    }
    if(allEmpty)
    {

    }
    else
    {
        DBDateaControler::getInstance()->query(queryInput);
    }

}

void FormQueryDialog::on_resetBtn_clicked()
{
    ui->companyInput->clear();
    ui->createdDateFromInput->clear();
    ui->createdDateToInput->clear();
    ui->emailInput->clear();
    ui->keyworkInput->clear();
    ui->locationInput->clear();
    ui->mobileInput->clear();
    ui->nameInput->clear();
    ui->orgInput->clear();
    ui->titleInput->clear();
}
