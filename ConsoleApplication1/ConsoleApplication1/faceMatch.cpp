#include "opencv2/opencv.hpp"
#include <windows.h>
#include <cstdio>  
#include <cstdlib>  
#include <iostream>
using namespace cv;
using namespace std;
class faceMatch{
private:
	Mat frame; Mat frame0;
	const char *pstrCascadeFileName = "D:\\GitHub\\opencv\\ConsoleApplication1\\Debug\\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	IplImage *pSrcImage = NULL;
	IplImage *pSrcImage0 = NULL;
	IplImage *pGrayImage = NULL;
	CvMemStorage *pcvMStorage = NULL;
	DWORD dwTimeBegin, dwTimeEnd;
	CvSeq *pcvSeqFaces = NULL;
public:
	int _Construct(){
		
	}
	void setframe(Mat newframe){
		this->frame = newframe;
	};
	Mat getframe(){
		return this->frame;
	}
	void loadFilter(){
		// ����Haar������������  
		// haarcascade_frontalface_alt.xmlϵOpenCV�Դ��ķ����� �������һ����ϵ��ļ�·�� 
		pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);
	}
	int runCamera(VideoCapture cap){
		 // open the default camera
		if (!cap.isOpened()) { // check if we succeeded
			return -1;
		}
		cap >> this->frame0;
			
		 // get a new this->frame from camera
		resize(frame0, frame, Size(160, 120), 0, 0, CV_INTER_LINEAR);
		return 0;
	}
	void faceMark(){
		this->pSrcImage = &IplImage(this->frame);
		this->pSrcImage0 = &IplImage(this->frame0);
		/*cout << this->pSrcImage0->height << "  " << this->pSrcImage0->width << endl;
		cout << this->pSrcImage->height << "  " << this->pSrcImage->width << endl;
		exit(0);*/
		pGrayImage = cvCreateImage(cvGetSize(this->pSrcImage), IPL_DEPTH_8U, 1);
		cvCvtColor(this->pSrcImage, pGrayImage, CV_BGR2GRAY);
		// ����ʶ������ 
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
			
			pcvMStorage = cvCreateMemStorage(0);
			cvClearMemStorage(pcvMStorage);
			// ʶ�� 
			dwTimeBegin = GetTickCount();
			pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);
			dwTimeEnd = GetTickCount();

			printf("Number of faces : %d   Identify available : %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);
			
			// ���  
			for (int i = 0; i <pcvSeqFaces->total; i++)
			{
				CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);
				CvPoint center;
				int radius;
				center.x = cvRound((r->x + r->width * 0.5)*(pSrcImage0->width / pSrcImage->width));
				center.y = cvRound((r->y + r->height * 0.5)*(pSrcImage0->height / pSrcImage->height));
				radius = cvRound((r->width + r->height) * 0.25*(pSrcImage0->height / pSrcImage->height));
				cvCircle(this->pSrcImage0, center, radius, FaceCirclecolors[i % 8], 2);
			}
			cvReleaseMemStorage(&pcvMStorage);
		}
		const char *pstrWindowsTitle = "Face recognition";
		cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);
		cvShowImage(pstrWindowsTitle, this->pSrcImage0);

		cvWaitKey(1);
	}
};