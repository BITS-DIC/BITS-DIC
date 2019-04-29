#include "class_img.h"
#include <fstream>

class_img::class_img() {
    // gs uses default constructor for struct_double_array
    max_gs = 0.0;
    // bcoef uses default constructor for struct_double_array
    border_bcoef = 0;
}

class_img::class_img(const class_img &ci2) {
    max_gs = ci2.max_gs;
    border_bcoef = ci2.border_bcoef;
    name = ci2.name;
    gs = ci2.gs;
    bcoef = ci2.bcoef;
}

class_img::class_img(cv::Mat input, std::string name) {
    this->name = name;
    max_gs = 0.0;
    border_bcoef = 20;
    gs.alloc(input.rows, input.cols);
    bcoef.alloc(input.rows + 2 * border_bcoef, input.cols + 2 * border_bcoef);
    cv::Mat temp, _bcoef;
    input.convertTo(temp, CV_64FC1, 1 / 255.0);

    for (int i = 0; i < temp.rows; i++) {
        const double *Mi = temp.ptr<double>(i);
        for (int j = 0; j < temp.cols; j++) {
            gs.value[i + j * temp.rows] = Mi[j];
            max_gs = std::max(max_gs, gs.value[i + j * temp.rows]);
        }
    }

    cv::copyMakeBorder(temp, _bcoef, border_bcoef, border_bcoef, border_bcoef, border_bcoef, cv::BORDER_REPLICATE);

    // Form kernel vector
    std::vector<double> kernel_b;
    std::vector<std::complex<double>> kernel_x; /* stores result of fourier on ker_x */
    kernel_b.push_back(11.0 / 20.0);
    kernel_b.push_back(13.0 / 60.0);
    kernel_b.push_back(1.0 / 120.0);
    for (int i = 3; i < _bcoef.cols - 2; i++) {
        kernel_b.push_back(0.0);
    }
    kernel_b.push_back(1.0 / 120.0);
    kernel_b.push_back(13.0 / 60.0);
    //FFT across kernel
    cv::dft(kernel_b, kernel_x, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

    std::vector<std::complex<double>> row_fft;
    for (int row = 0; row < _bcoef.rows; row++) {
        cv::dft(_bcoef.row(row), row_fft, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);
        for (int col = 0; col < _bcoef.cols; col++) {
            row_fft[col] /= kernel_x[col];
        }
        cv::dft(row_fft, _bcoef.row(row), cv::DFT_INVERSE | cv::DFT_ROWS | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
    }

    row_fft.clear();
    kernel_x.clear();
    kernel_b.clear();

    cv::Mat bcoef_t = _bcoef.t();

    kernel_b.push_back(11.0 / 20.0);
    kernel_b.push_back(13.0 / 60.0);
    kernel_b.push_back(1.0 / 120.0);
    for (int i = 3; i < bcoef_t.cols - 2; i++) {
        kernel_b.push_back(0.0);
    }
    kernel_b.push_back(1.0 / 120.0);
    kernel_b.push_back(13.0 / 60.0);
    cv::dft(kernel_b, kernel_x, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

    for (int row = 0; row < bcoef_t.rows; row++) {
        cv::dft(bcoef_t.row(row), row_fft, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);
        for (int col = 0; col < bcoef_t.cols; col++) {
            row_fft[col] /= kernel_x[col];
        }
        cv::dft(row_fft, bcoef_t.row(row), cv::DFT_INVERSE | cv::DFT_ROWS | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
    }

    row_fft.clear();
    kernel_x.clear();
    kernel_b.clear();

    _bcoef = bcoef_t.t();

    for (int i = 0; i < _bcoef.rows; i++) {
        const double *Mi = _bcoef.ptr<double>(i);
        for (int j = 0; j < _bcoef.cols; j++) {
            bcoef.value[i + j * _bcoef.rows] = Mi[j];
        }
    }
}
