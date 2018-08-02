#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src1, src2,dst;
	src1 = imread("F:\\小论文\\images\\lena.png");
	src2 = imread("F:\\小论文\\images\\opencv-logo.png");
	if (src1.empty())
	{
		cout << "cannot load the src1 image..." << endl;
	}
	if (src2.empty())
	{
		cout << "cannot load the src2 image..." << endl;
	}
	int alpha = 0.4;
	if (src1.size() == src2.size() && src1.type() == src2.type() && src1.channels() == src2.channels())
	{
		addWeighted(src1, alpha, src2, 1.0 - alpha, 0, dst);
		imshow("线性混合后的图像", dst);
	}
	else
	{
		cout << "the src1 and src2 images are not the same..." << endl;
	}
	waitKey(0);
	return 0;
}