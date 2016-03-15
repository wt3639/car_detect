#include <opencv/cv.h>
#include <opencv/highgui.h>
//#include <opencv/cv.hpp>
//#include <opencv2/opencv.hpp>
//#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

const char *  cascade_name = "E:\\car.xml";

void detec_and_draw(IplImage * img)
{
	static CvMemStorage * storage = 0;
	static CvHaarClassifierCascade * cascade = 0;
	int scale = 1;
	CvPoint pt1,pt2;

	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name,0,0,0);

	if(!cascade)
	{
		fprintf(stderr,"Error:could not load classifier cascade\n");
		return;
	}

	storage = cvCreateMemStorage(0);
	cvClearMemStorage(storage);
	//CvScalar s;
	//s.val[0] = 100;
	if(cascade)
	{
		CvSeq * car = cvHaarDetectObjects(img,cascade,storage,1.1,4,0,cvSize(10,10),cvSize(80,80));
		cout<<car->total<<endl;
		for(int i = 0; i<(car?car->total:0);i++)
		{
			CvRect * r = (CvRect*)cvGetSeqElem(car,i);

			pt1.x = r->x*scale;
			pt2.x = (r->x+r->width)*scale;
			pt1.y = r->y*scale;
			pt2.y = (r->y+r->height)*scale;

			cvRectangle(img,pt1,pt2,CV_RGB(230,20,232),1,8,0);
		}
	}

	namedWindow("result",1);
	cvShowImage("result",img);
	return;
}


int main(int argc, char** argv)
{
	//加载视频，并提取关键数据
	/*
	IplImage * momo = cvLoadImage("E:\\test1.jpg");
	namedWindow("grey_src",CV_WINDOW_AUTOSIZE);
	cvShowImage("grey_src",momo);
	//Mat img=imread("E:\\test1.jpg");
	//imshow("grey_src",img);
	//waitKey(6000);  
	*/
	
	CvCapture* capture = cvCaptureFromAVI("E:\\car3.avi");
	//IplImage * src = cvLoadImage("E:\\test1.jpg");
	IplImage *temp=NULL;
	temp = cvQueryFrame(capture);
	CvSize size = cvGetSize(temp);
	int chan = temp->nChannels;
	int depth = temp->depth;
	
	/*
	CvSize size = cvGetSize(src);
	int chan = src->nChannels;
	int depth = src->depth;
	*/
	
	IplImage * src = cvCreateImage(size,depth,chan);
	cvZero(src);
	IplImage * grey_src = cvCreateImage(size,depth,1);
	cvZero(grey_src);
	namedWindow("grey_src",CV_WINDOW_AUTOSIZE);

	int frameNum =1;
	int start = 100;
	while(1){
		temp = cvQueryFrame(capture);
		frameNum++;
		
		//if(frameNum == start)
		//{
			cvCopy(temp,src,NULL);

			cvCvtColor(src,grey_src,CV_BGR2GRAY);
			//Mat m(grey_src,true);
			//imshow("grey_src",m);
			cvShowImage("grey_src",grey_src);

			detec_and_draw(grey_src);
			cvWaitKey(10);  
		//	break;
		//}
		
	}

	cvWaitKey(0);
	
	//cvReleaseCapture(&capture);
	//cvReleaseImage(&src0);
	//cvReleaseImage(&src1);
	//cvReleaseImage(&temp);
	//cvReleaseImage(&grey_src);
	//cvReleaseImage(&grey_bg);
	//cvDestroyWindow("src");
	//cvDestroyWindow("diff_result");
	//cvDestroyWindow("diff_erode_result");
	//cvDestroyWindow("diff_dilate_result");
	//cvDestroyWindow("bg");
	return 0;
}