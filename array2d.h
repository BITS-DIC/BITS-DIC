#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <vector>

template <class T>
class Array2D {
    public:
        Array2D(int rows = 0, int cols = 0, T defValue = nullptr);
        ~Array2D();
        void setValue(T value, int row, int col);
        T getValue(int row, int col);
        int getRows()   ;
        int getCols();
    private:
        int rows;
        int cols;
        std::vector<std::vector<T>> data;
};

#endif // ARRAY2D_H
