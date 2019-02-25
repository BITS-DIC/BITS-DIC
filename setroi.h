#ifndef SETROI_H
#define SETROI_H

#include "class_roi.h"
#include "dic.h"
#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class SetROI;
}

class SetROI : public QDialog {
    Q_OBJECT

  public:
    explicit SetROI(QWidget *parent = nullptr, Dic *dic = nullptr);
    ~SetROI();
    class_roi roi;

  private slots:
    void on_setRoiLoadFromFile_clicked();
    void on_setRoiButtonBox_accepted();

  signals:
    void onRoiSet(class_roi);

  private:
    Ui::SetROI *ui;
    Dic *dic;

    //Image to hold roi data 255 <- include, 0 <- exclude
    class_integer_array region_mask;
    class_logical_array visited;
    int num_region;
    int rows;
    int cols;

    void bfs(int r, int c);
};

#endif // SETROI_H
