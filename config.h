#pragma once

#ifndef CONFIG_H
#define CONFIG_H

// Define the signs

// ENHANCEMENT: for difference only
// Comment "ENHANCEMENT" if not needed
#define ENHANCEMENT 10

#define ENABLE_OPTICAL_FLOW false
#define VISUALIZE_OF_DIRECTION false
#define DEFAULT_INPUT_VID "input.mp4"
#define DEFAULT_OUTPUT_VID "output.mp4"
#define DEFAULT_FOURCC 'X','2','6','4'

// Downsample only when optical flow is enabled
#if ENABLE_OPTICAL_FLOW
#define DOWNSAMPLE true
#else // ENABLE_OPTICAL_FLOW
#define DOWNSAMPLE false
#endif // ENABLE_OPTICAL_FLOW

// global vars
int VID_WIDTH = -1, VID_HEIGHT = -1;
bool CAMERA_ONLINE = false, OUTPUT_FILE = true;
long greater, less, pos, neg, summer;
float _greater, _less, _sum;

#endif // CONFIG_H
