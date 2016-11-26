#include "opencv2/opencv.hpp"
#include <windows.h>
#include <cstdio>  
#include <cstdlib>  
using namespace cv; 
using namespace std;
int doo();
int detect();
int main()
{
	doo();
	return 0;
}

int detect(){
	// 加载Haar特征检测分类器  
	// haarcascade_frontalface_alt.xml系OpenCV自带的分类器 下面是我机器上的文件路径 
	const char *pstrCascadeFileName = "D:\\Program Files (x86)\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);

	//VideoCapture cap(0); // open the default camera
	//	if (!cap.isOpened())  // check if we succeeded
	//		return -1;
	//Mat frame;
	//cap >> frame; // get a new frame from camera
	//IplImage qImg = IplImage(frame);
	//cvSaveImage("out.jpg", &qImg);

	// 载入图像 
	const char* pstrImageName = "out.jpg";
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);

	

	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

	// 人脸识别与标记 
	if (pHaarCascade != NULL)
	{
		CvScalar FaceCirclecolors[] =
		{
			{ 0, 0, 255 },
			{ 0, 128, 255 },
			{ 0, 255, 255 },
			{ 0, 255, 0 },
			{ 255, 128, 0 },
			{ 255, 255, 0 },
			{ 255, 0, 0 },
			{ 255, 0, 255 }
		};

		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage);
		// 识别 
		DWORD dwTimeBegin, dwTimeEnd;
		dwTimeBegin = GetTickCount();
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);
		dwTimeEnd = GetTickCount();

		printf("Number of faces : %d   Identify available : %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);

		// 标记  
		for (int i = 0; i <pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width * 0.5));
			center.y = cvRound((r->y + r->height * 0.5));
			radius = cvRound((r->width + r->height) * 0.25);
			cvCircle(pSrcImage, center, radius, FaceCirclecolors[i % 8], 2);
		}
		cvReleaseMemStorage(&pcvMStorage);
	}

	const char *pstrWindowsTitle = "Face recognition";
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsTitle, pSrcImage);

	//cvWaitKey(0);

	/*cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);*/
	return 0;
}
int doo(){
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	//namedWindow("camera", 1);
	for (int i=1;i<500;i++)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		//cvtColor(frame, edges);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		//imshow("camera", frame);
		IplImage qImg;
		qImg = IplImage(frame); // cv::Mat -> IplImage
		cvSaveImage("out.jpg", &qImg);
		/*char *pstrCascadeFileName = "out.jpg";
		detect(pstrCascadeFileName);*/
		detect();
		cout << i << endl;
		if (waitKey(30) >= 0) break;
		Sleep(500);
		
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}