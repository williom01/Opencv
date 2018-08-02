#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage, dstImage;
	//��ȡͼ��
	srcImage = imread("F:\\С����\\images\\lena.png");
	//�ж��Ƿ��Ѷ�ȡͼ��
	if (!srcImage.data)
	{
		printf("cannot find the srcImage");
	}

	dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	//����һ����Ĥ
	for (int row = 1; row < srcImage.rows-1; row++)
	{
		const uchar *previous = srcImage.ptr<uchar>(row-1);
		const uchar *current = srcImage.ptr<uchar>(row);
		const uchar *next = srcImage.ptr<uchar>(row + 1);
		uchar *outputImage = dstImage.ptr<uchar>(row);
		for (int col = srcImage.channels(); col < (srcImage.cols-1)*srcImage.channels(); col++)
		{
			outputImage[col] = saturate_cast<uchar>(5 * current[col] - (previous[col] + next[col] + current[col - srcImage.channels()] + current[col + srcImage.channels()]));
		}
	}

	//��������
	namedWindow("demo", CV_WINDOW_AUTOSIZE);
	imshow("demo", dstImage);
	waitKey(0);
	return 0;
}