#ifndef SETROI_H
#define SETROI_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class SetROI;
}

class SetROI : public QDialog
{
    Q_OBJECT

public:
    explicit SetROI(QWidget *parent = nullptr);
    ~SetROI();

private slots:
    void on_setRoiLoadFromFile_clicked();
    void on_setRoiButtonBox_accepted();

signals:
    void onRoiSet(cv::Mat);

private:
    Ui::SetROI *ui;

    //Image to hold roi data 255 <- include, 0 <- exclude
    cv::Mat roiImageMat;
};

#endif // SETROI_H
