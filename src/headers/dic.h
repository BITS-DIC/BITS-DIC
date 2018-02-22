#ifndef DIC_H
#define DIC_H
#include <opencv2/opencv.hpp>


class Dic
{
	public:
		Dic();
		~Dic();
		enum State {init=0, cur_img_loaded=2, ref_img_loaded=1};
		void setrefimg(cv::Mat);
		void setcurrimg(int /* Number of images */, cv::Mat * /* Pointer to array of images */);
		int getcurrimgcount();
		cv::Mat getcurrimg_i(int);
	private:
		cv::Mat refImage;
		cv::Mat *currImages;
		Dic::State state;
		int nCurrImages;    /* Number of current images */
};

#endif // DIC_H
