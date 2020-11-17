#include "opencv2/opencv.hpp"

int main(int argc, char* argv[]) {
	cv::Mat image_src = cv::Mat::zeros(720, 1280, CV_8UC3);
	std::vector<cv::Point2f> corners = {
		{220, 180}, {220, 700}, {1000, 700}, {1000, 180}
	};
	for (int k = 0; k < corners.size(); ++k) {
		cv::line(image_src, corners[(k + 1) % (corners.size())], corners[k], cv::Scalar(0, 255, 0), 3);
	}
	cv::imshow("result", image_src);
	cv::waitKey(0);

	return 0;
}