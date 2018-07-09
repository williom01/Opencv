#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;

int main()
{
	Mat srcImage = imread("F:\\1.jpg");
	imshow("srcImage", srcImage);
	waitKey(0);
	return 0;
}