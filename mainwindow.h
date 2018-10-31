#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define WINDOW_TITLE "BITS-DIC"

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include "dic.h"
#include "setroi.h"
#include <opencv2/opencv.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionLoad_Reference_Image_triggered();
        void on_actionLoad_Current_Image_s_triggered();
        void on_prevImage_clicked();
        void on_nextImage_clicked();
        void on_actionSet_Region_of_Interest_ROI_triggered();
        void on_actionPerform_DIC_Analysis_triggered();
        void onRoiSet(cv::Mat);

        void on_actionSet_DIC_Parameters_triggered();

private:
        Ui::MainWindow *ui;
        Dic *dic;
        SetROI *setRoiDialog;
        int currImgIndex;
        void setCurrentImageIndex(int);
};

#endif // MAINWINDOW_H
