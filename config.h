#pragma once

#ifndef CONFIG_H
#define CONFIG_H

// Define the signs
#define OUTPUT_FILE
// Comment "ENHANCEMENT" if not needed
#define ENHANCEMENT 5
#define CAMERA_ONLINE 0
#define DIY_FILE 1
#define DEFAULT_INPUT_VID "input.mp4"
#define DEFAULT_OUTPUT_VID "output.mp4"
#define DEFAULT_FOURCC 'X','2','6','4'

// global vars
int VID_WIDTH = -1, VID_HEITHT = -1;
long greater, less, pos, neg, summer;
float _greater, _less, _sum;

#endif // CONFIG_H
