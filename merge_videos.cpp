#include "opencv2/opencv.hpp"
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>

void getFiles(std::string path, std::vector<std::string>& files, std::vector<std::string> &names) {
	 ownname只存储文件的名称(eg.     data1.txt)*/

	 //文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if ((fileinfo.attrib &  _A_SUBDIR)) {  
			}
			else {
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				names.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
int main(int argc, char* argv[]) {
	std::string video_path = "F:\\xinaote\\cut_video";
	std::vector<std::string> files;
	std::vector<std::string> names;
	getFiles(video_path, files, names);
	std::cout << "name size: " << names.size() << std::endl;
	cv::VideoWriter writer;
	if (!writer.isOpened())
		writer.open("video_merged.mp4", CV_FOURCC('X', 'V', 'I', 'D'), 25, cv::Size(1280, 720));
	for (int i = 0; i < names.size(); ++i) {
		std::string name = names[i].substr(0, names[i].length() - 4);
		cv::VideoCapture cam;
		cam.open(files[i]);
		if (!cam.isOpened()) {
			std::cout << "open camera failed." << std::endl;
			return -1;
		}
		cv::Mat frame;
		while (cv::waitKey(1) != 'q') {
			cam >> frame;
			if (frame.empty()) {
				break;
			}
			
			cv::Mat frame_resized;
			cv::resize(frame, frame_resized, cv::Size(1280, 720));
			cv::putText(frame_resized, name.c_str(), cv::Point(0, 50), cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 255),2);
			writer << frame_resized;
			cv::imshow("result", frame_resized);
			cv::waitKey(30);
		}

		cam.release();
	}
	writer.release();

	system("pause");
	return 0;
}
