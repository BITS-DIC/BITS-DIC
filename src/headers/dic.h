#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>


class Dic
{
	public:
		Dic();
		~Dic();
		void setrefimg(cv::Mat);
		void setroi(cv::Mat);
		void setcurrimg(int /* Number of images */, cv::Mat * /* Pointer to array of images */);
		int getcurrimgcount();
		cv::Mat getcurrimg_i(int);
		cv::Mat getrefimg();
	private:
		cv::Mat refImage;
		cv::Mat *currImages;
		cv::Mat roi;	/* Region of Interest */
		int nCurrImages;    /* Number of current images */
};

#endif // DIC_H
