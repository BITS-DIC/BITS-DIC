#ifndef COLORMAP_H
#define COLORMAP_H
#include <QVector>
#include <QRgb>

class ColorMap {
    public:
        ColorMap(double minValue, double maxValue);
        QRgb getQRgb(double);
    private:
        double minValue;
        double maxValue;
        double range;
        QVector<QRgb> colorMap;
};

#endif // COLORMAP_H
