#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <vector>
#include <omp.h>

int main()
{

	cv::VideoCapture video(0);

	if (!video.isOpened())
		return -1;

	cv::Mat img, img_gray, img_edges;
	
	for (;;)
	{
		if (!video.read(img))
			break;

		if (img.empty())
			break;

		cv::cvtColor(img, img_gray, CV_BGR2GRAY);
		cv::Canny(img_gray, img_edges, 230, 460);

		std::vector<cv::Vec4i> lines;
		cv::HoughLinesP(img_edges, lines, 1, CV_PI / 180, 50, 25, 2);

#pragma omp parallel
		{
#pragma omp sections
			{
#pragma omp section
				{
					for (size_t i = 0; i < lines.size()/2; i++) {
						cv::Vec4i l = lines[i];
						cv::line(img,
							cv::Point(l[0], l[1]),
							cv::Point(l[2], l[3]),
							cv::Scalar(0, 255, 255),
							3
						);
					}
				}
#pragma omp section
				{
					for (size_t i = lines.size() / 2; i < lines.size(); i++) {
						cv::Vec4i l = lines[i];
						cv::line(img,
							cv::Point(l[0], l[1]),
							cv::Point(l[2], l[3]),
							cv::Scalar(0, 255, 255),
							3
						);
					}
				}
			}
		}

		for (size_t i = 0; i < lines.size(); i++) {
			cv::Vec4i l = lines[i];
			cv::line(img,
				cv::Point(l[0], l[1]),
				cv::Point(l[2], l[3]),
				cv::Scalar(0, 255, 255),
				3
			);
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