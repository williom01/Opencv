#include<opencv.hpp>
#include<opencv2\dnn.hpp>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::dnn;

//找到GoogleNet两个参数
String model_bin_file = "G:\\深度（机器）学习\\bvlc_googlenet.caffemodel";
String model_txt_file = "D:\\软件安装包\\opencv各种版本\\opencv-3.3.0\\samples\\data\\dnn\\bvlc_googlenet.prototxt";
String labels_txt_file = "D:\\软件安装包\\opencv各种版本\\opencv-3.3.0\\samples\\data\\dnn\\synset_words.txt";
vector<String> readLabels();
int main()
{
	Mat src = imread("C:\\Users\\William Liu\\Pictures\\风景\\1.jpg");
	if (src.empty())
	{
		cout << "cannot load the src image" << endl;
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("srcimage", src);

	vector<String> labels=readLabels();
	Net net = readNetFromCaffe(model_txt_file, model_bin_file);
	if (net.empty())
	{
		cout << "cannot read the net" << endl;
		return -1;
	}
	Mat inputBlob = blobFromImage(src, 1.0, Size(224, 224), Scalar(104, 117, 123));
	Mat prob;
	for (int i = 0; i < 10; i++)
	{
		net.setInput(inputBlob, "data");
		prob = net.forward("prob");
	}
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;
	double classPro;
	minMaxLoc(probMat, NULL, &classPro, NULL, &classNumber);
	int classidx = classNumber.x;
	printf("\n current image classfication:%s,possible:%.2f", labels.at(classidx).c_str(), classPro);

	putText(src, labels.at(classidx), Point(20, 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
	imshow("Image classfication", src);


	waitKey(0);
	return 0;
}

vector<String> readLabels() {
	vector<String> classNames;
	ifstream fp(labels_txt_file);
	if (!fp.is_open())
	{
		printf("cannot open the file");
		exit(-1);
	}
	string name;
	while (!fp.eof())
	{
		getline(fp, name);
		if (name.length())
		{
			classNames.push_back(name.substr(name.find(' ') + 1));
		}
	}
	fp.close();
	return classNames;
}