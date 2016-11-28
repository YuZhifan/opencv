#include "opencv2/opencv.hpp"
#include <windows.h>
#include <cstdio>  
#include <cstdlib>  
#include "faceMatch.cpp"
using namespace cv; 
using namespace std;

int main()
{
	faceMatch *fm = new faceMatch();
	fm->loadFilter();
	VideoCapture cap(0);

	for (;;){
		fm->runCamera(cap);
		fm->faceMark();
		
	}
	cvWaitKey(0);
	return 0;
}
