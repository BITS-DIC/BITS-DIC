#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define WINDOW_TITLE "BITS-DIC"

#include "class_img.h"
#include "class_roi.h"
#include "dic.h"
#include "displwindow.h"
#include "setroi.h"
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <opencv2/opencv.hpp>
#include <QEvent>
#include "setdicparams.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Dic *dic;

protected:
    void keyPressEvent(QKeyEvent *event);

  private slots:
    void on_actionLoad_Reference_Image_triggered();
    void on_actionLoad_Current_Image_s_triggered();
    void on_prevImage_clicked();
    void on_nextImage_clicked();
    void on_actionSet_Region_of_Interest_ROI_triggered();
    void on_actionPerform_DIC_Analysis_triggered();
    //Callbacks
    void onRoiSet(class_roi);
    void onParamsSet(Params params, bool success = true);

    void on_actionSet_DIC_Parameters_triggered();
    void on_actionShow_Displacements_triggered();

  private:
    Ui::MainWindow *ui;
    SetROI *setRoiDialog;
    SetDicParams *setDicParams;
    DisplWindow *displWindow;
    std::size_t currImgIndex;
    void setCurrentImageIndex(std::size_t);
};

#endif // MAINWINDOW_H
