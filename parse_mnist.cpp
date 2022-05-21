#include "opencv2/opencv.hpp"
#include <iostream>

#ifndef uchar
#	define uchar unsigned char
#endif 

int ReadNumber(FILE* fp, int len) {
	uchar* buffer = new uchar[len];
	fread(buffer, len, 1, fp);
	int result = 0;
	for (int i = 0; i < len; ++i) {
		int temp = buffer[i];
		result += temp << ((len - 1 - i) * 8);
	}
	delete[] buffer;
	return result;
}

void ReadImage(FILE* fp, int len, uchar* buffer) {
	fread(buffer, len, 1, fp);
}

int main() {
	const char* trainImgFile = "./train-images.idx3-ubyte";
	const char* trainLabelFile = "./train-labels.idx1-ubyte";

	FILE* imgIn = fopen(trainImgFile, "rb");
	if (imgIn == NULL) {
		std::cout << "open: " << trainImgFile << "failed." << std::endl;
		return -1;
	}
	fseek(imgIn, 0, 0);
	int imgMagic  = ReadNumber(imgIn, 4);
	int imgNum    = ReadNumber(imgIn, 4);
	int imgWidth  = ReadNumber(imgIn, 4);
	int imgHeight = ReadNumber(imgIn, 4);

	std::cout << "magic: " << imgMagic << " imgNum: " << imgNum << " imgWidth: " <<
		imgWidth << " imgHeight: " << imgHeight << std::endl;
	
	if (imgMagic != 2051) {
		std::cout << "error image magic number: " << imgMagic << std::endl;
		fclose(imgIn);
		return -1;
	}

	int imgSize = imgWidth * imgHeight;
	uchar* buffer = new uchar[imgSize];
	for (int i = 0; i < imgNum; ++i) {
		ReadImage(imgIn, imgSize, buffer);
		cv::Mat img = cv::Mat(imgHeight, imgWidth, CV_8UC1, buffer);
		cv::imwrite("train/image/" + std::to_string(i) + ".jpg", img);
	}
	delete[] buffer;
	fclose(imgIn);

	FILE* labelIn = fopen(trainLabelFile, "rb");
	int labelMagic = ReadNumber(labelIn, 4);
	int labelNum = ReadNumber(labelIn, 4);
	if (labelMagic != 2049) {
		std::cout << "error label magic number: " << labelMagic << std::endl;
		fclose(labelIn);
		return -1;
	}
	for (int i = 0; i < labelNum; ++i) {
		int label = ReadNumber(labelIn, 1);
		std::cout << "i: " << i << " label: " << label << std::endl;
	}


	fclose(labelIn);

	return 0;
}
