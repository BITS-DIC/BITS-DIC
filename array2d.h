#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <vector>

template <class T>
class Array2D {
    public:
        Array2D():Array2D(1,1) {}
        Array2D(std::size_t rows, std::size_t cols);
        ~Array2D();
        void setValue(T value, std::size_t row, std::size_t col);
        T getValue(std::size_t row, std::size_t col);
        std::size_t getRows()   ;
        std::size_t getCols();
    private:
        std::size_t rows;
        std::size_t cols;
        std::vector<std::vector<T>> data;
};

#endif // ARRAY2D_H
