#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

// the basic functions
bool CheckOpencvVersionOK()
{
#if (CV_VERSION_MAJOR < 4)
	printf("Your Opencv version is:");
	printf(CV_VERSION);
	printf(". Make sure you are using 4.0 or above.")
		getchar();
	return false;
#else
	// Opencv version is OK
	return true;
#endif
}


#endif // FUNCTIONS_H
