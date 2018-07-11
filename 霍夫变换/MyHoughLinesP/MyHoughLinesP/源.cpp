#include<opencv2\highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\胶囊\\胶囊9.jpg");
	Mat tempImage, dstImage;

	//边缘检测和灰度转换
	Canny(srcImage, tempImage, 50, 200, 3);
	cvtColor(tempImage, dstImage, COLOR_GRAY2BGR);

	//累积概率霍夫线变换
	vector<Vec4i> lines;
	HoughLinesP(tempImage, lines, 1, CV_PI / 180, 80, 50, 0);

	//绘制每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]),Scalar(186,8,255),1,LINE_AA);
	}
	imshow("【原始图】", srcImage);
	imshow("【边缘检测后的图像】", tempImage);
	imshow("【效果图】", dstImage);
	waitKey(0);
	return 0;
}