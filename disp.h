#ifndef DISP_H
#define DISP_H
#include <vector>

class Disp
{
public:
    Disp(unsigned int rows = 1, unsigned int cols = 1);
    ~Disp();
    unsigned int getRows();
    unsigned int getCols();
    void setValue(double val, unsigned int row, unsigned int col);
    double getValue(unsigned int row, unsigned int col);
private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> plot;
};

#endif // DISP_H
