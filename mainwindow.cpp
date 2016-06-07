#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "dbdateacontroler.h"
#include <QDebug>
#include "formquerydialog.h"
#include "formqueryresult.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginWin = new LoginDialog(this);
    loginWin->setModal(true);
    loginWin->installEventFilter(this);
    this->installEventFilter(this);
    loginWin->show();
    connect(loginWin,SIGNAL(login(QString,QString)),DBDateaControler::getInstance(),SLOT(loginVerify(QString,QString)));
    connect(DBDateaControler::getInstance(),SIGNAL(connectDBSuccess(bool)),loginWin,SLOT(loginResultHandler(bool)));

    FormQueryDialog* query = new FormQueryDialog();
    connect(query,SIGNAL(notLogin()),this,SLOT(notLoginHandler()));
    ui->verticalLayout->addWidget(query);
    FormQueryResult* queryResult = new FormQueryResult();
    ui->verticalLayout->addWidget(queryResult);
    connect(queryResult,SIGNAL(queryWindowControl()),query,SLOT(queryWindowControl()));
    FormJumpToolkit* toolkit = new FormJumpToolkit();
    ui->verticalLayout->addWidget(toolkit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug() << "received eventFilter message";
    if(this == obj)
    {
        if(QEvent::WindowDeactivate == event->type())
        {
            qDebug() << "received deactived message";
        }
        else if(QEvent::WindowActivate == event->type())
        {

        }
    }

    return QMainWindow::eventFilter(obj, event);;
}
void MainWindow::notLoginHandler()
{

    loginWin->setVisible(true);
}
