#include<opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src,dst;
	src = imread("F:\\小论文\\images\\lena.png");
	if (src.empty())
	{
		printf("cannot load the image...\n");
	}

	dst.create(src.size(), src.type());
	int height = dst.rows;
	int width = dst.cols;
	int channels = dst.channels();

	for (int row = 0; row < height; row++)
	{
		for (int col = 0;col < width;col++)
		{
			if (channels==1)
			{
				dst.at<uchar>(row, col) = 255 - src.at<uchar>(row, col);
			}
			else
			{
				dst.at<Vec3b>(row, col)[0] = 255 - src.at<Vec3b>(row, col)[0];
				dst.at<Vec3b>(row, col)[1] = 255 - src.at<Vec3b>(row, col)[1];
				dst.at<Vec3b>(row, col)[2] = 255 - src.at<Vec3b>(row, col)[2];
			}
		}
	}

	imshow("处理后的结果图", dst);
	waitKey(0);
	return 0;

	}

