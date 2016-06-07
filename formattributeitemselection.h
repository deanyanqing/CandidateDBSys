#ifndef FORMATTRIBUTEITEMSELECTION_H
#define FORMATTRIBUTEITEMSELECTION_H

#include <QDialog>
#include "common.h"
#include <vector>
namespace Ui {
class FormAttributeItemSelection;
}

typedef std::vector<ATTRIBUTES_DEF> ItemVisual;
class FormAttributeItemSelection : public QDialog
{
    Q_OBJECT

public:
    explicit FormAttributeItemSelection(QWidget *parent = 0);
    ~FormAttributeItemSelection();

signals:
    void itemVisualblitySetting(ItemVisual);

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::FormAttributeItemSelection *ui;
};

#endif // FORMATTRIBUTEITEMSELECTION_H
