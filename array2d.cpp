#include "array2d.h"
#include <stdexcept>

/**
 * std::size_t rows
 * std::size_t cols
 */
template<class T>
Array2D<T>::Array2D(std::size_t rows, std::size_t cols) {
    this->rows = rows;
    this->cols = cols;
    data.assign(this->rows, std::vector<T>(cols, 0));
}

template <class T>
Array2D<T>::~Array2D() {
    this->data.clear();
}

template <class T>
T Array2D<T>::getValue(std::size_t row, std::size_t col) {
    if(row >= this->rows || col >= this->cols) {
        throw std::out_of_range("Index out of range");
    }
    return data[row][col];
}

template <class T>
void Array2D<T>::setValue(T val, std::size_t row, std::size_t col) {
    if(row >= this->rows || col >= this->cols) {
        throw std::out_of_range("Index out of range");
    }
    data[row][col] = val;
}

template <class T>
std::size_t Array2D<T>::getRows() {
    return this->rows;
}

template <class T>
std::size_t Array2D<T>::getCols() {
    return this->cols;
}

//Possible types
template class Array2D<int>;
template class Array2D<double>;
