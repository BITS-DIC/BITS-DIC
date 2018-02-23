#include "src/headers/dic.h"

Dic::Dic()
{
    this->currentImagesCount = 0;
}

void Dic::setReferenceImage(const cv::Mat matrix)
{
    this->referenceImage = matrix;
}

void Dic::setROI(cv::Mat matrix)
{
	this->roi = matrix;
}


void Dic::setCurrentImages(int n, cv::Mat *list)
{
    this->currentImagesCount = n;
    this->currentImages = list;
}

cv::Mat Dic::getReferenceImage()
{
    return this->referenceImage;
}

int Dic::getCurrentImagesCount()
{
    return this->currentImagesCount;
}

cv::Mat Dic::getCurrentImage(int i)
{
    return this->currentImages[i];
}

Dic::~Dic()
{
    referenceImage.release();
    if (currentImages != NULL) {
        for (int i = 0; i < this->currentImagesCount; i++) {
            currentImages[i].release();
		}
        currentImages = NULL;
	}
}

