# Video Difference Measurement

Measure the difference between frames in videos. The brightness changes is measured using the average change in each pixel and channel respectively for those brighter and darker. Visualization is applied using the length of green blocks. The red value stand for the absolute value of changes.

![](./attachments/demo.jpg)

(Image captured from "Men's Long Jump Final | Rio 2016 Replay" on YouTube. Available at: https://www.youtube.com/watch?v=fXIbLmlUdOQ )

## Requirements

- Windows 10 x64
- Visual Studio 2019
- OpenCV 4.1.2

## Preparation

1. Download and install OpenCV at:

    https://sourceforge.net/projects/opencvlibrary/files/4.1.2/opencv-4.1.2-vc14_vc15.exe/download

2. Add `opencv\build\x64\vc15\bin` to the `Path` in your `Environment Variables`.

3. Open VS2019 and configure the OpenCV include and library directories in the properties "x64 Release".

    ![](./attachments/step1.png)

4. Copy the file `opencv_world412.dll` from `opencv\build\x64\vc15\bin` to `C:\Windows\System32` path. Then add the additional depandencies.

    ![](./attachments/step2.png)

5. Build from `main.cpp`.

## Usage

- Input the filename of the video for testing, and the output result filename. "*.mp4" is recommended.

- If you want to test a camera online, just modify line 10 to:

    `#define CAMERA_ONLINE 1`

- During running, press any key in video window to quit.
