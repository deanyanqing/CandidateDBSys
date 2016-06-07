#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class LoginDialog;
}

class QAbstractButton;
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void login(QString name,QString password);
public slots:
    void loginResultHandler(bool loginSucess);

private slots:
    void on_noname_login();

    void on_noname_reset();

    void on_noname_clicked(QAbstractButton *button);

private:
    void initButtons();
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
