#include "opencv2/opencv.hpp"

int main(int argc, char* argv[]) {
	const char* mask_file = "../images/mask.jpg";
	const char* img_file = "../images/image.jpg";
	cv::Mat img_mask = cv::imread(mask_file, 0);
	cv::Mat img_src = cv::imread(img_file, 1);

	cv::resize(img_mask, img_mask, cv::Size(img_src.cols, img_src.rows));
	cv::Mat mask = cv::Mat::zeros(img_mask.rows, img_mask.cols, CV_8UC3);
	for (int row = 0; row < img_src.rows; ++row) {
		for (int col = 0; col < img_src.cols; ++col) {
			mask.at<cv::Vec3b>(row, col)[1] = img_mask.at<uchar>(row, col);
		}
	}

	cv::addWeighted(img_src, 0.5f, mask, 1.0f, 0, mask);
	cv::imwrite("../images/image_merged.jpg", mask);
	cv::imshow("mask", mask);
	cv::waitKey(0);

	return 0;
}