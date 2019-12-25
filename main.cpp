/*
	---------- Video Difference Measurement ----------
	Measure the difference between frames in videos.
	The brightness changes is measured using the average change in each pixel and channel respectively for those brighter and darker.
	Visualization is applied using the length of green blocks.
	The red value stand for the absolute value of changes.

	1. Support video files with arbitrary size.
	2. Support real-time camera (experimental option).
	Copyright (C) 2019, Jiang Du, all rights reserved.
*/
#include "config.h"
#include "functions.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

using namespace cv;

int main(int argc, char* argv[], char* envp[])
{
#if (CV_VERSION_MAJOR < 4)
	printf("Your Opencv version is:");
	printf(CV_VERSION);
	printf(". Make sure you are using 4.0 or above.")
	getchar();
	return 1;
#else
	// Opencv version is OK
#endif
	char str0[255] = "";
	namedWindow("Video", WINDOW_AUTOSIZE);
	VideoCapture cap;
	Mat frame, last;
	
	// Get input filename
	printf("Input video:");
	gets_s(str0);
	// Input Enter only: Open web camera
	if (strlen(str0) < 1) CAMERA_ONLINE = true;
	
	// Try to open the video
	if (CAMERA_ONLINE) cap.open(0);
	else cap.open(str0);

	// TODO: check the file readable or camera available

	VID_WIDTH = cap.get(CAP_PROP_FRAME_WIDTH);
	VID_HEITHT = cap.get(CAP_PROP_FRAME_HEIGHT);

	// write to file or not
	Size size = Size(VID_WIDTH, VID_HEITHT);
	VideoWriter writer;
	printf("Output Name:");
	gets_s(str0);
	// input Enter only
	if (strlen(str0) < 1) strcpy(str0, DEFAULT_OUTPUT_VID);
	writer.open(str0, writer.fourcc(DEFAULT_FOURCC), 24, size, true);

	if (!cap.isOpened()) {
		//error in opening the video input
		printf("Unable to open video file!\n");
		return -1;
	}
	else
	{
		cap >> frame;
		if (frame.empty()) {
			printf("No frame.\n");
			return -2;
		}
		else
		{
			frame.copyTo(last);
			printf("Initialized.\n");
		}
	}
	while (1)
	{
		cap >> frame;
		// If no more frame then end
		if (frame.empty()) break;

#ifdef ENABLE_OPTICAL_FLOW
		// optical flow
		// use UMat for GPU acceleration
		UMat OF_last, OF_next;
		cvtColor(last, OF_last, COLOR_BGR2GRAY);
		cvtColor(frame, OF_next, COLOR_BGR2GRAY);
		UMat flow(OF_last.size(), CV_32FC2);
		calcOpticalFlowFarneback(OF_last, OF_next, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		// visualization
		Mat flow_cpu;
		flow.copyTo(flow_cpu);
		Mat flow_parts[2];
		split(flow_cpu, flow_parts);
		Mat magnitude, angle, magn_norm;
		cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
		normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
		angle *= ((1.f / 360.f) * (180.f / 255.f));
		//build hsv image
		Mat _hsv[3], hsv, hsv8, bgr;
		_hsv[0] = angle;
		_hsv[1] = Mat::ones(angle.size(), CV_32F);
		_hsv[2] = magn_norm;
		merge(_hsv, 3, hsv);
		hsv.convertTo(hsv8, CV_8U, 255.0);
		cvtColor(hsv8, bgr, COLOR_HSV2BGR);
		imshow("Video", bgr);
#else // ENABLE_OPTICAL_FLOW
		// calculate difference
		greater = 0, less = 0, pos = 0, neg = 0, summer = 0;
		// use "summer" instead of "sum" to avoid being ambigious
		for (register int i = 0; i < 3 * VID_WIDTH * VID_HEITHT; i++)
		{
			if ((*(frame.data + i)) > (*(last.data + i)))
			{
				// new greater
				*(last.data + i) = *(frame.data + i) - *(last.data + i);
				// last matrix stores the diff
				summer += *(last.data + i);
				greater += *(last.data + i);
				pos++;
			}
			else
			{
				*(last.data + i) -= *(frame.data + i);
				summer += *(last.data + i);
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
		_sum = float(summer) / (3 * VID_WIDTH * VID_HEITHT);
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
#endif // ENABLE_OPTICAL_FLOW


#ifdef ENABLE_OPTICAL_FLOW
		if (OUTPUT_FILE) writer.write(bgr);
#else
		if (OUTPUT_FILE) writer.write(last);
#endif // ENABLE_OPTICAL_FLOW
		if (waitKey(1) >= 0) break;

		// prepare for next frame
		frame.copyTo(last);
	}
	cap.release();
	if (OUTPUT_FILE) writer.release();
	getchar();
	return 0;
}