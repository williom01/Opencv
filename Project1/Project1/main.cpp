#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int OTSU(Mat Image);

int main()
{
	Mat srcImage = imread("F:\\1.jpg");
	Mat medianImage,gaussImage;
	//��һ����Ԥ����
	//1.�˲�ȥ�루����ֵ�˲����˹�˲���
	medianBlur(srcImage, medianImage, 5);
	GaussianBlur(medianImage, gaussImage, Size(5, 5), 0, 0);
	//2.�ҶȻ�����
	Mat grayImage;
	cvtColor(gaussImage, grayImage, COLOR_BGR2GRAY);//��ͨ���ҶȻ�����
	//3.ֱ��ͼ����
	//����ֱ��ͼ����
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0,255 };
	const float*ranges[1] = { pranges };
	MatND hist;
	//����ֱ��ͼ
	calcHist(&grayImage, 1,channels, Mat(), hist, 1, histSize, ranges);
	//��ʼ����������
	int hist_w = 500;
	int hist_h = 500;
	int nHistSize = 255;
	//����
	int bin_w = cvRound((double)hist_w / nHistSize);
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	//��ֱ��ͼ��һ����[0,histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//��ֱ��ͼ�����ϻ���ֱ��ͼ
	for (int i = 1; i < nHistSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1),
			hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i),
				hist_h - cvRound(hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	//��ʾֱ��ͼ
	imshow("ֱ��ͼ��", histImage);
	/*
	����ͼ��ֱ��ͼ��֪��ͼ���ж����ֵ��������ô����ֵ�㷨���ж�ֵ��������Ŀ��ͱ������ֿ�
	*/
	//4.�����ֵ���ж�ֵ������
	//����OTSU��ֵ���㷨�õ���ֵ
	int otsuThreshold = OTSU(grayImage);
	cout << "otsu����㷨�õ�����ֵ��" << otsuThreshold << endl;
	//����������ͼ��
	Mat otsuResultImage = Mat::zeros(grayImage.rows, grayImage.cols, CV_8UC1);
	//���õõ�����ֵʵ�ֶ�ֵ������
	for (int i = 0; i < grayImage.rows; i++)
	{
		for (int j = 0; j < grayImage.cols; j++)
		{
			//��������ֵ�ж�
			if (grayImage.at<uchar>(i,j)>otsuThreshold)
			{
				otsuResultImage.at<uchar>(i, j) = 255;
			}
			else
			{
				otsuResultImage.at<uchar>(i, j) = 0;
			}
		}
	}
	waitKey(0);
	return 0;
}

int OTSU(Mat srcImage)
{
	int nCols = srcImage.cols;
	int nRows = srcImage.rows;
	int threshold = 0;
	//��ʼ��ͳ�Ʋ���
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	//ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0;j < nRows;j++)
		{
			nSumPix[(int)srcImage.at<uchar>(j, i)]++;
		}
	}
	//����ÿ���Ҷȼ�ռ����ͼ���еĸ��ʷֲ�
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
	}
	//�����Ҷȼ�[0,255]������������䷽���µ���ֵ
	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 0; i < 256; i++)
	{
		//��ʼ����ز���
		w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;
		for (int j = 0; j < 256; j++)
		{
			//��������
			if (j<=i)
			{
				//��ǰiΪ�ָ���ֵ����һ���ܵĸ���
				w0 += nProDis[j];
				u0_temp += j*nProDis[j];
			}
			//ǰ������
			else
			{
				//��ǰiΪ�ָ���ֵ����һ���ܵĸ���
				w1 += nProDis[j];
				u1_temp += j*nProDis[j];
			}
		}
		//�ֱ��������ƽ���Ҷ�
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		delta_temp = (float)(w0*w1*pow((u0 - u1), 2));
		//�����ҵ������䷽���µ���ֵ
		if (delta_temp>delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}
	return threshold;
}
