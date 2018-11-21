#include "displwindow.h"
#include "ui_displwindow.h"
#include "array2d.h"
#include "utils.h"
#include "colormap.h"

DisplWindow::DisplWindow(QWidget *parent, Dic *dic) :
    QMainWindow(parent),
    ui(new Ui::DisplWindow)
{
    ui->setupUi(this);
    current = 0;
    this->dic = dic;

    //color the u/v displacements

    //work with fake data for now
    Array2D<int> disp(250, 400);
    int minVal = std::numeric_limits<int>::max();
    int maxVal = std::numeric_limits<int>::min();

    for(int i = 0; i < disp.getRows(); i++) {
        for(int j = 0; j < disp.getCols(); j++) {
            disp.setValue(i, i, j);
            minVal = std::min(minVal, i);
            maxVal = std::max(maxVal, i);
        }
    }

    QImage uImage(disp.getCols(), disp.getRows(), QImage::Format_ARGB32);
    ColorMap colormap(minVal, maxVal);

    for(int i = 0; i < disp.getRows(); i++) {
        for(int j = 0; j < disp.getCols(); j++) {
            uImage.setPixelColor(QPoint(j, i), colormap.getQRgb(disp.getValue(i, j)));
        }
    }

    Utils::loadImage(uImage, ui->label_ud_img);
    Utils::loadImage(uImage, ui->label_vd_img);

}

DisplWindow::~DisplWindow() {
    delete ui;
}

void DisplWindow::on_pbtn_left_clicked() {
    //TODO use dic object to get u/v displacement data and set accordingly
    current--;
    ui->label_curr_num->setNum(current);
}

void DisplWindow::on_pbtn_right_clicked() {
    //TODO use dic object to get u/v displacement data and set accordingly
    current++;
    ui->label_curr_num->setNum(current);
}

