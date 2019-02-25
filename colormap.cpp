#include "colormap.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

/**
 * @brief Initialise the MATLAB jet palette.
 * @param minValue Pass the minimum value of the intensities.
 * @param maxValue Pass the maximum value of the intensities.
 */
ColorMap::ColorMap(double minValue, double maxValue) {
    if (maxValue < minValue)
        std::swap(minValue, maxValue);

    this->minValue = minValue;
    this->maxValue = maxValue;
    this->range = maxValue - minValue;

    corners.push_back(0.0);
    corners.push_back(129.0 / this->steps);
    corners.push_back(384.0 / this->steps);
    corners.push_back(639.0 / this->steps);
    corners.push_back(894.0 / this->steps);
    corners.push_back(1.0);
}

/**
 * @brief Get QRgb object from given value. If value is outside range, minValue or maxValue will be used appropriately.
 * @param value Intensity value to convert to rgb.
 * @return QRgb value from colormap.
 */
QRgb ColorMap::getQRgb(double value) {

    if (value < minValue)
        value = minValue;
    else if (value > maxValue)
        value = maxValue;

    double fraction = (value - minValue) / this->range;
    int r, g, b;
    if (fraction <= corners[1]) {
        //blue increasing
        r = 0;
        g = 0;
        b = 127 + std::lround(fraction * this->steps);
    } else if (fraction > corners[1] && fraction <= corners[2]) {
        //no red, increasing green, full blue
        r = 0;
        g = std::lround(fraction * this->steps) - 128;
        b = 255;
    } else if (fraction > corners[2] && fraction <= corners[3]) {
        //increasing red, full green, reducing blue
        r = std::lround(fraction * this->steps) - 383;
        g = 255;
        b = 639 - std::lround(fraction * this->steps);
    } else if (fraction > corners[3] && fraction <= corners[4]) {
        //full red, reducing green, no blue
        r = 255;
        g = 895 - std::lround(fraction * this->steps);
        b = 0;
    } else {
        //red decreasing, no green, no blue
        r = this->steps - std::lround(fraction * this->steps) + 127;
        g = 0;
        b = 0;
    }

    r = std::min(r, 255);
    g = std::min(g, 255);
    b = std::min(b, 255);
    r = std::max(r, 0);
    g = std::max(g, 0);
    b = std::max(b, 0);

    return qRgb(r, g, b);
}
