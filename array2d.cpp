#include "array2d.h"

/**
 * int rows
 * int cols
 * T defValue
 * Provide default value for initialisation of array.
 */
template<class T>
Array2D<T>::Array2D(int rows, int cols, T defValue) {
    this->rows = rows;
    this->cols = cols;
    data.assign(this->rows, std::vector<T>(cols, defValue));
}

template <class T>
Array2D<T>::~Array2D() {
    this->data.clear();
}

template <class T>
T Array2D<T>::getValue(int row, int col) {
    return data[row][col];
}

template <class T>
void Array2D<T>::setValue(T val, int row, int col) {
    if(row < 0 || col < 0 || row >= this->rows || col >= this->cols) {
        return;
    }
    data[row][col] = val;
}

template <class T>
int Array2D<T>::getRows() {
    return this->rows;
}

template <class T>
int Array2D<T>::getCols() {
    return this->cols;
}

//Possible types
template class Array2D<int>;
