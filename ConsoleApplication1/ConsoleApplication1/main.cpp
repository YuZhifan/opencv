#include "opencv2/opencv.hpp"
#include <windows.h>
using namespace cv;
int main()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
	/*	cvtColor(frame, edges);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);*/
		imshow("camera", frame);
		if (waitKey(30) >= 0) break;
		Sleep(500);
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}