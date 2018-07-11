#include<opencv2\highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\胶囊\\胶囊9.jpg");
	Mat tempImage, dstImage;
	
	//Canny边缘检测
	Canny(srcImage, tempImage, 50, 200, 3);
	//灰度转换
	cvtColor(tempImage, dstImage, COLOR_GRAY2BGR);//将单通道图像转变成三通道图像

	//进行霍夫变换
	vector<Vec2f> lines;
	HoughLines(tempImage, lines, 1, CV_PI / 180, 150, 0, 0);

	//依次绘制每条线段
	for (size_t i = 0;  i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 450 * (-b));
		pt1.y = cvRound(y0 + 450 * (a));
		pt2.x = cvRound(x0 - 450 * (-b));
		pt2.y = cvRound(y0 - 450 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}
	imshow("【原始图】", srcImage);
	imshow("【边缘检测后的图】", tempImage);
	imshow("【效果图】", dstImage);

	waitKey(0);
	return 0;
}