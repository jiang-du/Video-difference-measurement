#pragma once

#ifndef CONFIG_H
#define CONFIG_H

// Define the signs

// ENHANCEMENT: for difference only
// Comment "ENHANCEMENT" if not needed
#define ENHANCEMENT 5

#define DOWNSAMPLE true

#define ENABLE_OPTICAL_FLOW
#define DEFAULT_INPUT_VID "input.mp4"
#define DEFAULT_OUTPUT_VID "output.mp4"
#define DEFAULT_FOURCC 'X','2','6','4'

// global vars
int VID_WIDTH = -1, VID_HEIGHT = -1;
bool CAMERA_ONLINE = false, OUTPUT_FILE = true;
long greater, less, pos, neg, summer;
float _greater, _less, _sum;

#endif // CONFIG_H
