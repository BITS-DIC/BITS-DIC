#include "src/headers/dic.h"

Dic::Dic()
{
	this->nCurrImages = 0;
}

void Dic::setrefimg(const cv::Mat matrix)
{
	this->refImage = matrix;
}

void Dic::setroi(cv::Mat matrix)
{
	this->roi = matrix;
}

void Dic::setcurrimg(int n, cv::Mat *list)
{
	this->nCurrImages = n;
	this->currImages = list;
}

cv::Mat Dic::getrefimg()
{
	return this->refImage;
}

int Dic::getcurrimgcount()
{
	return this->nCurrImages;
}

cv::Mat Dic::getcurrimg_i(int i)
{
	return this->currImages[i];
}

Dic::~Dic()
{
	refImage.release();
	if (currImages != NULL) {
		for (int i = 0; i < this->nCurrImages; i++) {
			currImages[i].release();
		}
		currImages = NULL;
	}
}

