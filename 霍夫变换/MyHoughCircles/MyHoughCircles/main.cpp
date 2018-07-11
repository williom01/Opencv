#include<opencv2\highgui.hpp>
#include<imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\药片\\药片13.jpg");
	Mat tempImage, dstImage;

	//灰度转换和高斯滤波去噪
	cvtColor(srcImage, tempImage, COLOR_BGR2GRAY);
	GaussianBlur(tempImage, tempImage, Size(3, 3), 0, 0);

	//进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(tempImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 75, 0, 0);
	//绘制圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		
		int radius = cvRound(circles[i][2]);
cout << "圆心坐标：" << center << "，  此圆半径："<<radius<<endl;
		//圆心绘制
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);

	}
	imshow("【效果图】", srcImage);
	waitKey(0);
	return 0;
}