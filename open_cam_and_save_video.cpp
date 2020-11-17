#include <iostream>
#include "opencv2/opencv.hpp"

const char kWindowName[] = "Mirror";

int main(int argc, char* argv[]) {
	std::string input_video_path;
	std::string output_video_path = "result.mp4";
	cv::VideoCapture capture;
	const bool load_video = !input_video_path.empty();
	if (load_video) {
		capture.open(input_video_path);
	} else {
		capture.open(0);
	}
	if (!capture.isOpened()) {
		std::cerr << "open camera failed.\n" << std::endl;
		return -1;
	}

	cv::VideoWriter writer;
	const bool save_video = !output_video_path.empty();
	if (!save_video) {
		cv::namedWindow(kWindowName, /*flags=cv::WINDOW_AUTOSIZE*/1);
#if (CV_MAJOR_VERSION >= 3) && (CV_MINOR_VERSION >= 2)
		capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
		capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
		capture.set(cv::CAP_PROP_FPS, 30);
#endif
	}

	std::cout << "start capture video." << std::endl;
	bool grap_frame = true;
	cv::Mat frame;
	while (grap_frame) {
		capture >> frame;
		if (frame.empty()) break;
		if (save_video) {
			//CV_FOURCC('P', 'I', 'M', '1') = MPEG - 1 codec
			//CV_FOURCC('M', 'J', 'P', 'G') = motion - jpeg codec
			//CV_FOURCC('M', 'P', '4', '2') = MPEG - 4.2 codec
			//CV_FOURCC('D', 'I', 'V', '3') = MPEG - 4.3 codec
			//CV_FOURCC('D', 'I', 'V', 'X') = MPEG - 4 codec
			//CV_FOURCC('U', '2', '6', '3') = H263 codec
			//CV_FOURCC('I', '2', '6', '3') = H263I codec
			//CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
			std::cout << "prepare video writer." << std::endl;
			if (!writer.isOpened()) {
				writer.open(output_video_path.c_str(),
					cv::VideoWriter::fourcc('P', 'I', 'M', '1'), 
					25/*capture.get(cv::CAP_PROP_FPS)*/,
					frame.size());
			}
			writer.write(frame);
		} else {
			cv::imshow(kWindowName, frame);
			const int pressed_key = cv::waitKey(5);
			if (pressed_key >= 0 && pressed_key <= 255) grap_frame = false;
		}
	}
	std::cout << "success." << std::endl;
	if (writer.isOpened()) writer.release();
	if (capture.isOpened()) capture.release();

	return 0;
}