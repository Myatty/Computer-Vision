#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core/utils/logger.hpp>

using namespace std;
using namespace cv;

int main() {

    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    Mat frame;
    VideoCapture cap;
    double fps, delay, duration;
    int total_frames, maxFrameCount, frameCount;

    if (cap.open("background.mp4") == 0) {
        cout << "Can't Open Such File!!!" << endl;
        waitKey(0);
        return -1;  
    }

    fps = cap.get(CAP_PROP_FPS);
    //cout << "FPS: " << fps << endl;

    maxFrameCount = static_cast<int>(fps * 3);  // first 3 seconds

    delay = cvRound(1000 / fps);
    //cout << "Delay: " << delay<<" ms"<< endl;

    total_frames = cap.get(CAP_PROP_FRAME_COUNT);
    //cout << "Total Frames: " << total_frames << endl;

    duration = total_frames / fps;
    //cout << "Duration of the Video: " << duration <<" secs" << endl;

    frameCount = 0;

    while (frameCount < maxFrameCount) {

        cap >> frame; 

        if (frame.empty()) break;  

        imshow("Video", frame);  

        if (waitKey(delay) >= 0) break;
        
        frameCount++;
        cout << "Frames: " << frameCount << " / " << total_frames << endl;
    }

    cap.release();

    return 0;
}
