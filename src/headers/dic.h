#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>

class Dic
{
	public:
		Dic();
		~Dic();
		void setReferenceImage(cv::Mat);
		void setROI(cv::Mat);
		void setCurrentImages(int /* Number of images */, cv::Mat * /* Pointer to array of images */);
		void computeBcoef();
		int getCurrentImagesCount();
		cv::Mat getCurrentImage(int);
		cv::Mat getReferenceImage();
		cv::Mat getImgGradX();
		cv::Mat getImgGradY();
	private:
		cv::Mat referenceImage;
		cv::Mat *currentImages;
		cv::Mat roi;	/* Region of Interest */
		cv::Mat bcoeff;
		int currentImagesCount;	/* Number of current images */
		cv::Mat refImgGradX;	/* (d/dx) (f) */
		cv::Mat refImgGradY;	/* (d/dy) (f) */

};

#endif // DIC_H
