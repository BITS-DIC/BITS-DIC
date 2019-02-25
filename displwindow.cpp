#include "displwindow.h"
#include "array2d.h"
#include "colormap.h"
#include "ui_displwindow.h"
#include "utils.h"
#include <QDebug>
#include <QString>

DisplWindow::DisplWindow(QWidget *parent, Dic *dic) : QMainWindow(parent),
                                                      ui(new Ui::DisplWindow) {
    ui->setupUi(this);
    current = 0;
    this->dic = dic;

    if (dic->cimgs.size() == 0)
        return;
    for (std::size_t currImage = 0; currImage < dic->cimgs.size(); currImage++) {
        double minValu = std::numeric_limits<double>::max();
        double maxValu = -1.0 * std::numeric_limits<double>::max();

        double minValv = std::numeric_limits<double>::max();
        double maxValv = -1.0 * std::numeric_limits<double>::max();

        for (int i = 0; i < dic->plot_u[currImage].height; i++) {
            for (int j = 0; j < dic->plot_u[currImage].width; j++) {
                if (dic->plot_validpoints[currImage].value[i + j * dic->plot_validpoints[currImage].height]) {
                    minValu = std::min(minValu, dic->plot_u[currImage].value[i + j * dic->plot_u[currImage].height]);
                    maxValu = std::max(maxValu, dic->plot_u[currImage].value[i + j * dic->plot_u[currImage].height]);

                    minValv = std::min(minValv, dic->plot_v[currImage].value[i + j * dic->plot_v[currImage].height]);
                    maxValv = std::max(maxValv, dic->plot_v[currImage].value[i + j * dic->plot_v[currImage].height]);
                }
            }
        }

//        qDebug() << "minValu is " << minValu;
//        qDebug() << "maxValu is " << maxValu;

//        qDebug() << "minValv is " << minValv;
//        qDebug() << "maxValv is " << maxValv;

        plot_u.push_back(QImage());
        plot_v.push_back(QImage());

        //information in bounds does not change
        bounds.push_back(minValu);
        bounds.push_back(maxValu);
        bounds.push_back(minValv);
        bounds.push_back(maxValv);

        //current min max..can change any time with call to setImage
        cminmax.push_back(minValu);
        cminmax.push_back(maxValu);
        cminmax.push_back(minValv);
        cminmax.push_back(maxValv);

        setImages(currImage);
    }
    setPlots(0);
    ui->slider_u_lb->setValue(static_cast<int>((cminmax[0] - bounds[0]) * DPI));
    ui->slider_u_ub->setValue(static_cast<int>((cminmax[1] - bounds[1]) * DPI));
    ui->slider_v_lb->setValue(static_cast<int>((cminmax[2] - bounds[2]) * DPI));
    ui->slider_v_ub->setValue(static_cast<int>((cminmax[3] - bounds[3]) * DPI));

    ui->pbtn_left->setEnabled(false);
    if (dic->cimgs.size() <= 1)
        ui->pbtn_right->setEnabled(false);
}

void DisplWindow::setImages(std::size_t currImage, double minValu, double maxValu, double minValv, double maxValv) {
    cminmax[0 + currImage * 4] = minValu;
    cminmax[1 + currImage * 4] = maxValu;
    cminmax[2 + currImage * 4] = minValv;
    cminmax[3 + currImage * 4] = maxValv;

    setImages(currImage);
}

void DisplWindow::setImages(std::size_t currImage) {
    double minValu = cminmax[0 + currImage * 4];
    double maxValu = cminmax[1 + currImage * 4];
    double minValv = cminmax[2 + currImage * 4];
    double maxValv = cminmax[3 + currImage * 4];

    QImage uImage(dic->plot_u[currImage].width, dic->plot_u[currImage].height, QImage::Format_ARGB32);
    ColorMap colormapu(minValu, maxValu);
    for (int i = 0; i < dic->plot_u[currImage].height; i++) {
        for (int j = 0; j < dic->plot_u[currImage].width; j++) {
            if (dic->plot_validpoints[currImage].value[i + j * dic->plot_validpoints[currImage].height]) {
                uImage.setPixelColor(QPoint(j, i), colormapu.getQRgb(dic->plot_u[currImage].value[i + j * dic->plot_u[currImage].height]));
            } else {
                uImage.setPixelColor(QPoint(j, i), qRgb(0, 0, 0));
            }
        }
    }

    QImage vImage(dic->plot_v[currImage].width, dic->plot_v[currImage].height, QImage::Format_ARGB32);
    ColorMap colormapv(minValv, maxValv);

    for (int i = 0; i < dic->plot_v[currImage].height; i++) {
        for (int j = 0; j < dic->plot_v[currImage].width; j++) {
            if (dic->plot_validpoints[currImage].value[i + j * dic->plot_validpoints[currImage].height]) {
                vImage.setPixelColor(QPoint(j, i), colormapv.getQRgb(dic->plot_v[currImage].value[i + j * dic->plot_v[currImage].height]));
            } else {
                vImage.setPixelColor(QPoint(j, i), qRgb(0, 0, 0));
            }
        }
    }
    plot_u[currImage] = uImage;
    plot_v[currImage] = vImage;
}

void DisplWindow::setPlots(std::size_t currImage) {
    ui->label_curr_num->setNum(static_cast<int>(currImage + 1));
    ui->label_curr_name->setText(QString::fromStdString(dic->cimgs[currImage].name));

    ui->label_u_ub_min->setNum(bounds[0 + currImage * 4]);
    ui->label_u_ub_max->setNum(bounds[1 + currImage * 4]);
    ui->label_u_lb_min->setNum(bounds[0 + currImage * 4]);
    ui->label_u_lb_max->setNum(bounds[1 + currImage * 4]);
    ui->label_v_ub_min->setNum(bounds[2 + currImage * 4]);
    ui->label_v_ub_max->setNum(bounds[3 + currImage * 4]);
    ui->label_v_lb_min->setNum(bounds[2 + currImage * 4]);
    ui->label_v_lb_max->setNum(bounds[3 + currImage * 4]);

    Utils::loadImage(plot_u[currImage], ui->label_ud_img, 512, 2);
    Utils::loadImage(plot_v[currImage], ui->label_vd_img, 512, 2);
}

void DisplWindow::on_pbtn_left_clicked() {
    current--;

    ui->pbtn_right->setEnabled(true);
    if (current == 0)
        ui->pbtn_left->setEnabled(false);

    setPlots(current);
}

void DisplWindow::on_pbtn_right_clicked() {
    current++;

    ui->pbtn_left->setEnabled(true);
    if (current == dic->cimgs.size() - 1)
        ui->pbtn_right->setEnabled(false);

    setPlots(current);
}

DisplWindow::~DisplWindow() {
    delete ui;
    plot_u.clear();
    plot_v.clear();
    bounds.clear();
    cminmax.clear();
}

void DisplWindow::on_slider_u_lb_valueChanged(int value) {
    double stepu = bounds[1 + current * 4] - bounds[0 + current * 4];
    stepu /= DPI;
    double minValu = bounds[0 + current * 4] + value * stepu;
    ui->label_u_lb->setText(QString("Lowerbound (%1)").arg(minValu));
    setImages(current, minValu, cminmax[1 + current * 4], cminmax[2 + current * 4], cminmax[3 + current * 4]);
    setPlots(current);
}

void DisplWindow::on_slider_u_ub_valueChanged(int value) {
    double stepu = bounds[1 + current * 4] - bounds[0 + current * 4];
    stepu /= DPI;
    double maxValu = bounds[0 + current * 4] + value * stepu;
    ui->label_u_ub->setText(QString("Upperbound (%1)").arg(maxValu));
    setImages(current, cminmax[0 + current * 4], maxValu, cminmax[2 + current * 4], cminmax[3 + current * 4]);
    setPlots(current);
}

void DisplWindow::on_slider_v_lb_valueChanged(int value) {
    double stepv = bounds[3 + current * 4] - bounds[2 + current * 4];
    stepv /= DPI;
    double minValv = bounds[2 + current * 4] + value * stepv;
    ui->label_v_lb->setText(QString("Lowerbound (%1)").arg(minValv));
    setImages(current, cminmax[0 + current * 4], cminmax[1 + current * 4], minValv, cminmax[3 + current * 4]);
    setPlots(current);
}

void DisplWindow::on_slider_v_ub_valueChanged(int value) {
    double stepv = bounds[3 + current * 4] - bounds[2 + current * 4];
    stepv /= DPI;
    double maxValv = bounds[2 + current * 4] + value * stepv;
    ui->label_v_ub->setText(QString("Upperbound (%1)").arg(maxValv));
    setImages(current, cminmax[0 + current * 4], cminmax[1 + current * 4], cminmax[2 + current * 4], maxValv);
    setPlots(current);
}
