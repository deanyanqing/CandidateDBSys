#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->passwdInput->setEchoMode(QLineEdit::Password);

    initButtons();
}

const static QString LOGIN_STR="&Login";
const static QString RESET_STR="&Reset";

void LoginDialog::initButtons()
{
    QPushButton* loginButton = new QPushButton(LOGIN_STR);
    loginButton->setDefault(true);

    QPushButton* resetButton = new QPushButton(RESET_STR);
    resetButton->setCheckable(true);
    resetButton->setAutoDefault(false);

    ui->noname->addButton(loginButton, QDialogButtonBox::ActionRole);
    ui->noname->addButton(resetButton, QDialogButtonBox::ActionRole);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_noname_login()
{
    QString user= ui->userInput->text();
    QString passwd = ui->passwdInput->text();
    if(user.isEmpty() || passwd.isEmpty())
    {
        QMessageBox::warning(this, tr("Login Procedure"),
                                       tr("Please type your user and password."
                                          "Blank is not allowed!"), QMessageBox::Ok);

        return ;
    }
    else
    {
        emit this->login(user,passwd);
    }

    //this->setVisible(false);
}

void LoginDialog::on_noname_reset()
{
    ui->userInput->clear();
    ui->passwdInput->clear();
}

void LoginDialog::loginResultHandler(bool loginSucess)
{
    if(loginSucess)
    {

        this->setVisible(false);
    }
    else
    {
        QMessageBox::warning(this, tr("Login Procedure"),
                                       tr("Invliad user or password."
                                          "Please double check!"), QMessageBox::Ok);
    }
}

void LoginDialog::on_noname_clicked(QAbstractButton *button)
{
    if(0 == button->text().compare(LOGIN_STR))
    {
        on_noname_login();
    }
    else
    {
        on_noname_reset();
    }
}
