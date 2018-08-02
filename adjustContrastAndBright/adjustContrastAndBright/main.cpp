#include<opencv2\opencv.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int main()
{
	Mat src,dst;
	src = imread("F:\\小论文\\images\\lena.png");
	if (!src.data)
	{
		cout << "can not load the image" << endl;
	}
	dst=Mat::zeros(src.size(), src.type());
	
	int alpha = 11;
	int belta = 10;
	int height = src.rows;
	int width = src.cols;
	int channels = src.channels();

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (channels==1)
			{
				dst.at<uchar>(row, col) = saturate_cast<uchar>(alpha*src.at<uchar>(row, col)+belta);
			}
			else if (channels==3)
			{
				/*float b = m.at<Vec3f>(row, col)[0];
				float g = m.at<Vec3f>(row, col)[1];
				float r = m.at<Vec3f>(row, col)[2];*/
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*src.at<Vec3b>(row, col)[0] +belta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*src.at<Vec3b>(row, col)[1] +belta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*src.at<Vec3b>(row, col)[2] +belta);
			}
		}
	}

	imshow("效果图显示", dst);
	waitKey(0);
	return 0;
}