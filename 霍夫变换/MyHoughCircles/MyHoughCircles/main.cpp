#include<opencv2\highgui.hpp>
#include<imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\ҩƬ\\ҩƬ13.jpg");
	Mat tempImage, dstImage;

	//�Ҷ�ת���͸�˹�˲�ȥ��
	cvtColor(srcImage, tempImage, COLOR_BGR2GRAY);
	GaussianBlur(tempImage, tempImage, Size(3, 3), 0, 0);

	//���л���Բ�任
	vector<Vec3f> circles;
	HoughCircles(tempImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 75, 0, 0);
	//����Բ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		
		int radius = cvRound(circles[i][2]);
cout << "Բ�����꣺" << center << "��  ��Բ�뾶��"<<radius<<endl;
		//Բ�Ļ���
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);

	}
	imshow("��Ч��ͼ��", srcImage);
	waitKey(0);
	return 0;
}