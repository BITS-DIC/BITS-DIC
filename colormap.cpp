#include "colormap.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

/**
 * @brief Initialise the MATLAB jet palette.
 * @param minValue Pass the minimum value of the intensities.
 * @param maxValue Pass the maximum value of the intensities.
 */
ColorMap::ColorMap(double minValue, double maxValue) {
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->range = maxValue - minValue;

    QFile file(QString(":/colormap.txt"));
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error loading colormap from text file!";
    } else {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" ");
            colorMap.append(qRgb(fields[0].toInt(), fields[1].toInt(), fields[2].toInt()));
        }
        qInfo() << "Loading colormap text file!";
    }
    file.close();
}

/**
 * @brief Get QRgb object from given value. If value is outside range, minValue or maxValue will be used appropriately.
 * @param value Intensity value to convert to rgb.
 * @return QRgb value from colormap.
 */
QRgb ColorMap::getQRgb(double value) {
    if(value < minValue) {
        value = minValue;
    } else if(value > maxValue) {
        value = maxValue;
    }

    int k = static_cast<int>(74.0 * ((value - minValue) / range));
    k = std::min(k, 74);
    if(k >=0 && k <= 74)
        return colorMap[k];
    else {
        return qRgb(0, 0, 127);
    }
}
