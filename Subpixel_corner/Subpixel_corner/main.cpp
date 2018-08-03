#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

const char* output_title = "subpixel_corner detection";
void SubPixel_Demo(int, void*);
Mat src,src_gray;
int max_count = 50;
int max_corners = 50;
int main(int argc, char*argv) {
	src = imread("F:\\Ð¡ÂÛÎÄ\\images\\lena.png");
	if (src.empty())
	{
		printf("cannot load the image...\n"); 
		return -1;
	}
	namedWindow("src image", CV_WINDOW_AUTOSIZE);
	imshow("src image", src);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	createTrackbar("Corners:",output_title,&max_corners,max_count,SubPixel_Demo);
	SubPixel_Demo(0, 0);

	waitKey(0);
	return 0;
}
void SubPixel_Demo(int, void*) {
	if (max_corners<5)
	{
		max_corners = 5;
	}
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	goodFeaturesToTrack(src_gray, corners, max_corners, qualityLevel, minDistance, Mat(), blockSize, false, k);
	printf("numbers of corners:%d\n", corners.size());
	Mat resultImg = src.clone();
	for (size_t t = 0; t < corners.size(); t++)
	{
		circle(resultImg, corners[t], 2, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow(output_title, resultImg);

	Size winSize = Size(5, 5);
	Size zerozone = Size(-1, -1);
	TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.0001);
	cornerSubPix(src_gray, corners, winSize, zerozone, tc);

	for (size_t t = 0; t < corners.size(); t++)
	{
		cout << (t + 1) << ".point[x,y]=" << corners[t].x << "," << corners[t].y << endl;
	}
	return;
}