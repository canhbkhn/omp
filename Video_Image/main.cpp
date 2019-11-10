#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>


int main()
{
	cv::VideoCapture video("cars.avi");
	

	cv::Ptr<cv::ORB> detector = cv::ORB::create(10000);
	//detector = cv::ORB::create();
	std::vector<cv::KeyPoint> keypoints;

	if (!video.isOpened())
		return -1;

	for (;;)
	{
		cv::Mat img;
		video >> img;

		if (img.empty())
			break;

		detector->detect(img, keypoints);

//#pragma omp parallel
//		{
//#pragma omp sections
//			{
//#pragma omp section
//				{
//					for (size_t i = 0; i < keypoints.size() / 2; ++i) {
//						cv::circle(img, keypoints[i].pt, 2,
//							cv::Scalar(0, 0, 255), 1);
//					}
//				}
//
//#pragma omp section
//				{
//					for (size_t i = keypoints.size() / 2; i < keypoints.size(); ++i) {
//						cv::circle(img, keypoints[i].pt, 2,
//							cv::Scalar(0, 0, 255), 1);
//					}
//				}
//			}
//		}
		//cv::imshow("img", img);

		

		for (size_t i = 0; i < keypoints.size(); ++i) {
			cv::circle(img, keypoints[i].pt, 2,
				cv::Scalar(0, 0, 255), 1);
		}

		cv::imshow("img", img);

		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}

	video.release();

	cvDestroyAllWindows();

	return 0;
}