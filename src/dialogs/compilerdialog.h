/* - DownZemAll! - Copyright (C) 2019 Sebastien Vavassori
 */

#ifndef DIALOGS_COMPILER_DIALOG_H
#define DIALOGS_COMPILER_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

namespace Ui {
class CompilerDialog;
}

class CompilerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompilerDialog(QWidget *parent = Q_NULLPTR);
    ~CompilerDialog();

private slots:
    void on_okButton_released();

private:
    Ui::CompilerDialog *ui;
};

#endif // DIALOGS_COMPILER_DIALOG_H