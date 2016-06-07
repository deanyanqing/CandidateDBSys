#ifndef FORMJUMPTOOLKIT_H
#define FORMJUMPTOOLKIT_H

#include <QWidget>

namespace Ui {
class FormJumpToolkit;
}

class FormJumpToolkit : public QWidget
{
    Q_OBJECT

public:
    explicit FormJumpToolkit(QWidget *parent = 0);
    ~FormJumpToolkit();

     void updatePageIndex(int current,int total);
private slots:
    void on_textEdit_textChanged();

    void on_homeBtn_clicked();

    void on_previousBtn_clicked();

    void on_nextBtn_clicked();

    void on_endBtn_clicked();

    void on_jumpToInput_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::FormJumpToolkit *ui;
    int currentPageIndex;
    int totalPages;
};

#endif // FORMJUMPTOOLKIT_H
