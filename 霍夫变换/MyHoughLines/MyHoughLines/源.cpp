#include<opencv2\highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\����\\����9.jpg");
	Mat tempImage, dstImage;
	
	//Canny��Ե���
	Canny(srcImage, tempImage, 50, 200, 3);
	//�Ҷ�ת��
	cvtColor(tempImage, dstImage, COLOR_GRAY2BGR);//����ͨ��ͼ��ת�����ͨ��ͼ��

	//���л���任
	vector<Vec2f> lines;
	HoughLines(tempImage, lines, 1, CV_PI / 180, 150, 0, 0);

	//���λ���ÿ���߶�
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
	imshow("��ԭʼͼ��", srcImage);
	imshow("����Ե�����ͼ��", tempImage);
	imshow("��Ч��ͼ��", dstImage);

	waitKey(0);
	return 0;
}