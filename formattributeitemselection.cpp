#include "formattributeitemselection.h"
#include "ui_formattributeitemselection.h"

FormAttributeItemSelection::FormAttributeItemSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAttributeItemSelection)
{
    ui->setupUi(this);
    this->setWindowTitle("Item Setting");
    ui->chName->setChecked(true);
    ui->company->setChecked(true);
    ui->detail->setChecked(true);
    ui->eamil->setChecked(true);
    ui->enName->setChecked(true);
    ui->gender->setChecked(true);
    ui->location->setChecked(true);
    ui->orgnization->setChecked(true);
    ui->tag->setChecked(true);
    ui->title->setChecked(true);
    ui->timerstamp->setChecked(true);
    ui->mobile->setChecked(true);
}

FormAttributeItemSelection::~FormAttributeItemSelection()
{
    delete ui;
}

void FormAttributeItemSelection::on_okBtn_clicked()
{
    this->setVisible(false);
    ItemVisual items;
    if(ui->chName->isChecked())
    {
        items.push_back(ATTR_CHINDES_NAME);
    }
    if(ui->company->isChecked())
    {
        items.push_back(ATTR_COMPANY);
    }
    if(ui->detail->isChecked())
    {
        items.push_back(ATTR_GENERAL_INFO);
    }
    if(ui->eamil->isChecked())
    {
        items.push_back(ATTR_EMAIL);
    }
    if(ui->enName->isChecked())
    {
        items.push_back(ATTR_ENGLISH_NAME);
    }
    if(ui->gender->isChecked())
    {
        items.push_back(ATTR_GENDER);
    }
    if(ui->location->isChecked())
    {
        items.push_back(ATTR_LOCATION);
    }
    if(ui->orgnization->isChecked())
    {
        items.push_back(ATTR_ORGNAZATION);
    }
    if(ui->tag->isChecked())
    {
        items.push_back(ATTR_LABEL);
    }
    if(ui->timerstamp->isChecked())
    {
        items.push_back(ATTR_TIME_STAMP);
    }
    if(ui->title->isChecked())
    {
        items.push_back(ATTR_TITLE);
    }
    if(ui->mobile->isChecked())
    {
         items.push_back(ATTR_MOBILE);
    }
    emit itemVisualblitySetting(items);
}

void FormAttributeItemSelection::on_cancelBtn_clicked()
{
    this->setVisible(false);
}
