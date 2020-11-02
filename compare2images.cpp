#include "opencv2/opencv.hpp"

int main(int argc, char* argv[]) {

	const char* img_file1 = "../images/image_mask.jpg";
	const char* img_file2 = "../images/image_mask_old.jpg";

	cv::Mat image1 = cv::imread(img_file1, -1);
	cv::Mat image2 = cv::imread(img_file2, -1);
	std::cout << image1.channels() << " " << image2.channels() << std::endl;
	cv::Mat diff;
	cv::absdiff(image1, image2, diff);
	int number_non_zero = cv::countNonZero(diff);
	std::cout << "number non zero: " << number_non_zero << std::endl;
	cv::imwrite("../images/mask_diff.jpg", diff);

	cv::imshow("diff_image", diff);
	cv::waitKey(0);

	return 0;
}