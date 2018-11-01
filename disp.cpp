#include "disp.h"
#include <QtDebug>
#include <limits>

Disp::Disp(int rows, int cols)
{
    rows = std::max(0, rows);
    cols = std::max(0, cols);
    this->rows = rows;
    this->cols = cols;

    this->minValue = std::numeric_limits<double>::max();
    this->maxValue = std::numeric_limits<double>::min();
    plot.assign(this->rows, std::vector<double>(this->cols, 0));
}

Disp::~Disp() {
    plot.clear();
}

void Disp::setValue(double value, int row, int col) {
    if(row < 0 || col < 0) {
        qDebug() << QString("row(%1) or col(%2) lesser than 0!")
                    .arg(row)
                    .arg(col);
    } else if(row >= getRows() || col >= getCols()) {
        qDebug() << QString("row(%1) or col(%2) greater than max allowed Row(%3) and Col(%4)")
                    .arg(row)
                    .arg(col)
                    .arg(getRows())
                    .arg(getCols());
    } else {
        plot[row][col] = value;
        minValue = std::min(minValue, value);
        maxValue = std::max(maxValue, value);
    }
}

double Disp::getValue(int row, int col) {
    if(row < 0 || col < 0) {
        qDebug() << QString("row(%1) or col(%2) lesser than 0!")
                    .arg(row)
                    .arg(col);
    } else if(row >= getRows() || col >= getCols()) {
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

int Disp::getRows() {
    return rows;
}

int Disp::getCols() {
    return cols;
}

double Disp::getMinValue() {
    return minValue;
}

double Disp::getMaxValue() {
    return maxValue;
}
