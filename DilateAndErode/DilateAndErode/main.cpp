#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src, dst;
int elementSize = 1;
int max_Size = 20;
void CallBack_Demo(int, void*);
const char* output_title = "Dilate result image";
int main(int argc, char** argv) {
	src = imread("F:\\1.jpg");
	if (!src.data)
	{
		printf("cannot find the image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	createTrackbar("Element Size:", output_title, &elementSize, max_Size, CallBack_Demo);
	CallBack_Demo(0, 0);

	waitKey(0);
	return 0;
}
void CallBack_Demo(int, void*) {
	int s = elementSize * 2 + 1;
	Mat StructElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	dilate(src, dst, StructElement, Point(-1, -1));
	imshow(output_title, dst);
	return;
}