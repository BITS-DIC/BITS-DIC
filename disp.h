#ifndef DISP_H
#define DISP_H
#include <vector>

class Disp
{
public:
    Disp(int rows = 1, int cols = 1);
    ~Disp();
    int getRows();
    int getCols();
    void setValue(double val, int row, int col);
    double getValue(int row, int col);
    double getMinValue();
    double getMaxValue();
private:
    double minValue;
    double maxValue;
    int rows;
    int cols;
    std::vector<std::vector<double>> plot;
};

#endif // DISP_H
