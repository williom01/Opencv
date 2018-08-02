#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

void corner_harris(int, void*);
Mat src, src_gray;
int blockSize = 2;
int ksize = 3;
double k = 0.04;
const char * output_title = "corner_harris detection result";
int main()
{
	int thresh = 130;
	int count = 255;
	src = imread("F:\\小论文\\images\\lena.png");
	if (src.empty())
	{
		cout << "cannot find the image" << endl;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	createTrackbar("Thresh:", output_title, &thresh, count, corner_harris);
	corner_harris(0, 0);

	waitKey(0);
	return 0;
}

void corner_harris(int, void *)
{
	Mat dst, dst_norm,dst_normScale;
	int thresh = 20;
	dst = Mat::zeros(src_gray.size(), CV_32FC1);

	cornerHarris(src_gray, dst, blockSize, ksize, k,BORDER_CONSTANT);//对灰度图像进行角点检测处理。
	
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1);//最小可能会达到几十，最大可能会达到上千  为此下一步需要进行归一化处理到（0，255）
	convertScaleAbs(dst_norm, dst_normScale);
	Mat resultImage = src.clone();
	for (int row = 0; row <resultImage.rows; row++)
	{
		uchar* currentRow = dst_normScale.ptr(row);
		for (int  col = 0; col < resultImage.cols; col++)
		{
			int value = (int)*currentRow;
			if (value>thresh)
			{
				circle(resultImage, Point(col, row), 2, Scalar(0, 0, 255), 2, 8, 0);
			}
			currentRow++;
		}
	}
	imshow(output_title, resultImage);
}
