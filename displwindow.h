#ifndef DISPLWINDOW_H
#define DISPLWINDOW_H

#include "dic.h"
#include <QMainWindow>
#define DPI 100

namespace Ui {
class DisplWindow;
}

class DisplWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit DisplWindow(QWidget *parent = nullptr, Dic *dic = nullptr);
    ~DisplWindow();

  private slots:
    void on_pbtn_right_clicked();
    void on_pbtn_left_clicked();
    void on_slider_u_ub_valueChanged(int value);
    void on_slider_u_lb_valueChanged(int value);
    void on_slider_v_ub_valueChanged(int value);
    void on_slider_v_lb_valueChanged(int value);

private:
    Dic *dic;
    std::size_t current;
    Ui::DisplWindow *ui;
    void setPlots(std::size_t currImg);
    void setImages(std::size_t);
    void setImages(std::size_t, double, double, double, double);
    std::vector<QImage> plot_u;
    std::vector<QImage> plot_v;
    std::vector<double> cminmax;
    std::vector<double> bounds;
};

#endif // DISPLWINDOW_H
