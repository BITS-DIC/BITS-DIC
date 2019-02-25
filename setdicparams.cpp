#include "setdicparams.h"
#include "params.h"
#include "ui_setdicparams.h"
#include <QIntValidator>

SetDicParams::SetDicParams(QWidget *parent) : QDialog(parent),
                                              ui(new Ui::SetDicParams) {
    ui->setupUi(this);

    //Set limits to line edits
    ui->slider_radius->setMinimum(10);
    ui->slider_radius->setMaximum(60);
    ui->slider_radius->setValue(21);
    ui->label_radius_info->setText("Radius = 21");

    ui->slider_spacing->setMinimum(1);
    ui->slider_spacing->setMaximum(10);
    ui->slider_spacing->setValue(5);
    ui->label_spacing_info->setText("Spacing = 5");

    //TODO veriy extremes with Ncorr
    ui->le_citr->setValidator(new QIntValidator(0, 50, this));
    ui->le_cdif->setValidator(new QDoubleValidator(0, 100, 10, this));

    ui->le_citr->setText("50");
    ui->le_cdif->setText("0.000001");
}

void SetDicParams::on_slider_radius_valueChanged(int value) {
    ui->label_radius_info->setText(QString("Radius = %1").arg(value));
}

void SetDicParams::on_slider_spacing_valueChanged(int value) {
    ui->label_spacing_info->setText(QString("Spacing = %1").arg(value));
}

void SetDicParams::on_btnBox_accepted() {
    //Emit signal that Dic params are set
    Params params;

    //TODO fix seeds
    int seedX = 44;
    int seedY = 0;

    params.subsetSize = ui->slider_radius->value();
    params.subsetSpacing = ui->slider_spacing->value();
    params.cutoff_iteration = ui->le_citr->text().toInt();
    params.cutoff_diffnorm = ui->le_cdif->text().toDouble();
    params.seedPoint = std::make_pair(seedX, seedY);

    emit onParamsSet(params);
}

//If window is closed
void SetDicParams::reject() {
    emit onParamsSet(Params(), false);
    QDialog::reject();
}

void SetDicParams::on_btnBox_rejected() {
    emit onParamsSet(Params(), false);
    QDialog::reject();
}

SetDicParams::~SetDicParams() {
    delete ui;
}
