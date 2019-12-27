#include "functions.hpp"

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

bool VideoOpticalFlow()
{
	return false;
}