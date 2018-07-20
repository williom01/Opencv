#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int OTSU(Mat Image);

int main()
{
	Mat srcImage = imread("F:\\1.jpg");
	Mat medianImage,gaussImage;
	//第一步：预处理
	//1.滤波去噪（先中值滤波后高斯滤波）
	medianBlur(srcImage, medianImage, 5);
	GaussianBlur(medianImage, gaussImage, Size(5, 5), 0, 0);
	//2.灰度化处理
	Mat grayImage;
	cvtColor(gaussImage, grayImage, COLOR_BGR2GRAY);//单通道灰度化处理
	//3.直方图处理
	//定义直方图参数
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0,255 };
	const float*ranges[1] = { pranges };
	MatND hist;
	//计算直方图
	calcHist(&grayImage, 1,channels, Mat(), hist, 1, histSize, ranges);
	//初始化画布参数
	int hist_w = 500;
	int hist_h = 500;
	int nHistSize = 255;
	//区间
	int bin_w = cvRound((double)hist_w / nHistSize);
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	//将直方图归一化到[0,histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//在直方图画布上画出直方图
	for (int i = 1; i < nHistSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1),
			hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i),
				hist_h - cvRound(hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	//显示直方图
	imshow("直方图：", histImage);
	/*
	根据图像直方图可知，图像有多个峰值，因而采用大津阈值算法进行二值化处理，将目标和背景区分开
	*/
	//4.大津阈值进行二值化处理
	//调用OTSU二值化算法得到阈值
	int otsuThreshold = OTSU(grayImage);
	cout << "otsu大津算法得到的阈值：" << otsuThreshold << endl;
	//定义输出结果图像
	Mat otsuResultImage = Mat::zeros(grayImage.rows, grayImage.cols, CV_8UC1);
	//利用得到的阈值实现二值化操作
	for (int i = 0; i < grayImage.rows; i++)
	{
		for (int j = 0; j < grayImage.cols; j++)
		{
			//高像素阈值判断
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
	//初始化统计参数
	int nSumPix[256];
	float nProDis[256];
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	//统计灰度级中每个像素在整幅图像中的个数
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0;j < nRows;j++)
		{
			nSumPix[(int)srcImage.at<uchar>(j, i)]++;
		}
	}
	//计算每个灰度级占整幅图像中的概率分布
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
	}
	//遍历灰度级[0,255]，计算出最大类间方差下的阈值
	float w0, w1, u0_temp, u1_temp, u0, u1, delta_temp;
	double delta_max = 0.0;
	for (int i = 0; i < 256; i++)
	{
		//初始化相关参数
		w0 = w1 = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;
		for (int j = 0; j < 256; j++)
		{
			//背景部分
			if (j<=i)
			{
				//当前i为分割阈值，第一类总的概率
				w0 += nProDis[j];
				u0_temp += j*nProDis[j];
			}
			//前景部分
			else
			{
				//当前i为分割阈值，第一类总的概率
				w1 += nProDis[j];
				u1_temp += j*nProDis[j];
			}
		}
		//分别计算各类的平均灰度
		u0 = u0_temp / w0;
		u1 = u1_temp / w1;
		delta_temp = (float)(w0*w1*pow((u0 - u1), 2));
		//依次找到最大类间方差下的阈值
		if (delta_temp>delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}
	return threshold;
}
