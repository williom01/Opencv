#include<opencv2\highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("C:\\Users\\William Liu\\Desktop\\images\\����\\����9.jpg");
	Mat tempImage, dstImage;

	//��Ե���ͻҶ�ת��
	Canny(srcImage, tempImage, 50, 200, 3);
	cvtColor(tempImage, dstImage, COLOR_GRAY2BGR);

	//�ۻ����ʻ����߱任
	vector<Vec4i> lines;
	HoughLinesP(tempImage, lines, 1, CV_PI / 180, 80, 50, 0);

	//����ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]),Scalar(186,8,255),1,LINE_AA);
	}
	imshow("��ԭʼͼ��", srcImage);
	imshow("����Ե�����ͼ��", tempImage);
	imshow("��Ч��ͼ��", dstImage);
	waitKey(0);
	return 0;
}