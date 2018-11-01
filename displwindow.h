#ifndef DISPLWINDOW_H
#define DISPLWINDOW_H

#include <QMainWindow>
#include "dic.h"

namespace Ui {
class DisplWindow;
}

class DisplWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplWindow(QWidget *parent = nullptr, Dic *dic  = nullptr);
    ~DisplWindow();

private slots:
    void on_pbtn_right_clicked();
    void on_pbtn_left_clicked();

private:
    int current;
    Dic *dic;
    Ui::DisplWindow *ui;

};

#endif // DISPLWINDOW_H
