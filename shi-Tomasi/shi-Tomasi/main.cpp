#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void ShiTomasi(int, void*);
const char* output_title = "shi-Tomasi corner detection demo";
Mat src, src_gray;
int value = 25;
int max_corners = 200;
double k = 0.04;
RNG rng(12345);
int main(int argc, char**agrv) {
	Mat src = imread("F:\\Ð¡ÂÛÎÄ\\images\\lena.png");
	if (src.empty())
	{
		printf("cannot load the image...\n");
		return -1;
	}
	namedWindow("src image", CV_WINDOW_AUTOSIZE);
	imshow("src image", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	createTrackbar("value:",output_title,&value, max_corners,ShiTomasi);
	ShiTomasi(0, 0);

	waitKey(0);
	return 0;
}

void ShiTomasi(int, void *)
{
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	Mat resultImg = src_gray.clone();
	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
	goodFeaturesToTrack(src_gray, corners, max_corners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
	printf("numbers of corners:%d\n", corners.size());
	
	
	for (size_t i = 0; i < corners.size(); i++)
	{
		circle(resultImg, corners[i], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
	}
	imshow(output_title, resultImg);	
}
