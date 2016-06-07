#ifndef FORMQUERYDIALOG_H
#define FORMQUERYDIALOG_H

#include <QWidget>
#include "common.h"
namespace Ui {
class FormQueryDialog;
}

typedef std::map<ATTRIBUTES_DEF,QString> QueryInput;

class FormQueryDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FormQueryDialog(QWidget *parent = 0);
    ~FormQueryDialog();

signals:
    void notLogin();
private slots:
    void on_queryBtn_clicked();
    void queryWindowControl();
    void on_resetBtn_clicked();

private:
    Ui::FormQueryDialog *ui;
};

#endif // FORMQUERYDIALOG_H
