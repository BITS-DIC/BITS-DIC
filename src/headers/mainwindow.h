#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define WINDOW_TITLE "BITS-DIC"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_Reference_Image_triggered();

    void on_actionLoad_Current_Image_s_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
