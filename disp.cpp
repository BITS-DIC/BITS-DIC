#include "disp.h"
#include <QtDebug>

Disp::Disp(unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    plot.assign(this->rows, std::vector<double>(this->cols, 0));
}

Disp::~Disp() {
    plot.clear();
}

void Disp::setValue(double value, unsigned int row, unsigned int col) {
    if(row >= getRows() || col >= getCols()) {
        qDebug() << QString("row(%1) or col(%2) greater than max allowed Row(%3) and Col(%4)")
                    .arg(row)
                    .arg(col)
                    .arg(getRows())
                    .arg(getCols());
    } else {
        plot[row][col] = value;
    }
}

double Disp::getValue(unsigned int row, unsigned int col) {
    if(row >= getRows() || col >= getCols()) {
        qDebug() << QString("row(%1) or col(%2) greater than max allowed Row(%3) and Col(%4)")
                    .arg(row)
                    .arg(col)
                    .arg(getRows())
                    .arg(getCols());
    } else {
        return plot[row][col];
    }
    return 0;
}

unsigned int Disp::getRows() {
    return rows;
}

unsigned int Disp::getCols() {
    return cols;
}
