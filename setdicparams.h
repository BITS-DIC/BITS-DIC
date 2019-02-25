#ifndef SETDICPARAMS_H
#define SETDICPARAMS_H

#include "dic.h"
#include <QDialog>

namespace Ui {
class SetDicParams;
}

class SetDicParams : public QDialog {
    Q_OBJECT

  public:
    explicit SetDicParams(QWidget *parent = nullptr);
    ~SetDicParams();

  signals:
    void onParamsSet(Params params, bool success = true);

  private slots:
    void on_slider_radius_valueChanged(int value);
    void on_slider_spacing_valueChanged(int value);
    void on_btnBox_accepted();
    void on_btnBox_rejected();
    void reject();

  private:
    Ui::SetDicParams *ui;
};

#endif // SETDICPARAMS_H
