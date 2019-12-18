/*
	---------- Find the different between frames in videos ----------
	1. Support video files with arbitrary size.
	2. Support real-time camera (experimental option).
	Copyright (C) 2019, Jiang Du, all rights reserved.
*/
#define OUTPUT_FILE
// Comment "ENHANCEMENT" if not needed
#define ENHANCEMENT 5
#define CAMERA_ONLINE 0
#define DIY_FILE 1
#define DEFAULT_INPUT_VID "test_input.mp4"
#define DEFAULT_OUTPUT_VID "output.mp4"
#define DEFAULT_FOURCC 'X','2','6','4'
// Do NOT uncomment the following 2 lines!!!
//#define VID_WIDTH 1920
//#define VID_HEITHT 1080

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
int VID_WIDTH = -1, VID_HEITHT = -1;

int main()
{
	char str0[255]="";
	namedWindow("Video", WINDOW_AUTOSIZE);
	VideoCapture cap;
#if CAMERA_ONLINE
	// web camera
	cap.open(0);
#else
#if DIY_FILE
	printf("Input video:");
	gets_s(str0);
	// input Enter only
	if (strlen(str0) < 1) strcpy(str0, DEFAULT_INPUT_VID);
#else
	strcpy(str0, DEFAULT_INPUT_VID);
#endif
	cap.open(str0);
#endif // CAMERA_ONLINE
	VID_WIDTH = cap.get(CAP_PROP_FRAME_WIDTH);
	VID_HEITHT = cap.get(CAP_PROP_FRAME_HEIGHT);
	// write to file or not
#ifdef OUTPUT_FILE
	Size size = Size(VID_WIDTH, VID_HEITHT);
	VideoWriter writer;
#if DIY_FILE
	printf("Output Name:");
	gets_s(str0);
	// input Enter only
	if (strlen(str0) < 1) strcpy(str0, DEFAULT_OUTPUT_VID);
#else
	strcpy(str0, DEFAULT_OUTPUT_VID);
#endif
	writer.open(str0, writer.fourcc(DEFAULT_FOURCC), 24, size, true);
#endif // OUTPUT_FILE
	Mat frame, last;
	long greater, less, pos, neg, sum;
	float _greater, _less, _sum;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		if (last.empty())
		{
			// First frame
			frame.copyTo(last);
			printf("Initialized.\n");
			continue;
		}
		// calculate difference
		greater = 0, less = 0, pos = 0, neg = 0, sum = 0;
		for (register int i = 0; i < 3 * VID_WIDTH * VID_HEITHT; i++)
		{
			if ((*(frame.data + i)) > (*(last.data + i)))
			{
				// new greater
				*(last.data + i) = *(frame.data + i) - *(last.data + i);
				// last matrix stores the diff
				sum += *(last.data + i);
				greater += *(last.data + i);
				pos++;
			}
			else
			{
				*(last.data + i) -= *(frame.data + i);
				sum += *(last.data + i);
				less += *(last.data + i);
				neg++;
			}

#ifdef ENHANCEMENT
			if (*(last.data + i) < int(255 / ENHANCEMENT))
				* (last.data + i) *= ENHANCEMENT;
			else *(last.data + i) = 255;
#endif // ENHANCEMENT

		}
		_greater = float(greater) / (3 * VID_WIDTH * VID_HEITHT);
		_less = float(less) / (3 * VID_WIDTH * VID_HEITHT);
		_sum = float(sum) / (3 * VID_WIDTH * VID_HEITHT);
		printf("Brighter: %f,\tDarker: %f\n", _greater, _less);

		// print rectangle on image
		sprintf(str0, "Brighter");
		putText(last, str0, Point(50, 75), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 8, 0);
		sprintf(str0, "%5.2f", _greater);
		putText(last, str0, Point(350, 75), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 8, 0);
		Rect rect1(540, 40, int(50 * _greater), 35);
		cv::rectangle(last, rect1, Scalar(0, 255, 0), -1, LINE_8, 0);

		sprintf(str0, "Darker");
		putText(last, str0, Point(50, 150), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 8, 0);
		sprintf(str0, "%5.2f", _less);
		putText(last, str0, Point(350, 150), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 8, 0);
		Rect rect2(540, 115, int(50 * _less), 35);
		cv::rectangle(last, rect2, Scalar(0, 255, 0), -1, LINE_8, 0);

		sprintf(str0, "Changed");
		putText(last, str0, Point(50, 225), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 255), 2, 8, 0);
		sprintf(str0, "%5.2f", _sum);
		putText(last, str0, Point(350, 225), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 255), 2, 8, 0);
		Rect rect3(540, 190, int(50 * _less), 35);
		cv::rectangle(last, rect3, Scalar(0, 0, 255), -1, LINE_8, 0);

		imshow("Video", last);
#ifdef OUTPUT_FILE
		writer.write(last);
#endif // OUTPUT_FILE
		if (waitKey(1) >= 0) break;

		// prepare for next frame
		frame.copyTo(last);
	}
	cap.release();
#ifdef OUTPUT_FILE
	writer.release();
#endif // OUTPUT_FILE
	getchar();
	return 0;
}