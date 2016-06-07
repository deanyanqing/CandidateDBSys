#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
     bool eventFilter(QObject *obj, QEvent *ev);
private slots:
    void notLoginHandler();


private:
    Ui::MainWindow *ui;
    LoginDialog* loginWin;
};

#endif // MAINWINDOW_H
