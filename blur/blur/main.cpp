#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src,dst;
	src = imread("F:\\Ğ¡ÂÛÎÄ\\images\\lena.png");
	if (!src.data)
	{
		cout << "cannot load the src image" << endl;
	}
	char input_title[] = "input image";
	char output_title[] = "blur image";
	namedWindow(input_title, CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(input_title, src);
	blur(src, dst, Size(3, 3), Point(-1, -1));
	imshow(output_title, dst);


	waitKey(0);
	return 0;
}