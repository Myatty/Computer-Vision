#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// Function to perform gamma correction
void gammaCorrection(const Mat& src, Mat& dst, float gamma) {
    CV_Assert(gamma >= 0);
    Mat lut(1, 256, CV_8UC1);
    uchar* p = lut.ptr();
    for (int i = 0; i < 256; i++) {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
    }
    LUT(src, lut, dst);
}

int main() {
    // Read the image in grayscale
    Mat grayImage = imread("lena.png", IMREAD_GRAYSCALE);
    if (grayImage.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Rotate the image 90 degrees clockwise
    Mat rotatedImage;
    transpose(grayImage, rotatedImage);
    flip(rotatedImage, rotatedImage, 0); // Change the flip code to 0 for clockwise rotation

    // Create a result image for transformations
    Mat resultImage = rotatedImage.clone();

    // Perform the negative or gamma transformation
    for (int y = 0; y < rotatedImage.rows; y++) {
        for (int x = 0; x < rotatedImage.cols; x++) {
            if (rotatedImage.at<uchar>(y, x) < 127) {
                // Negative transformation
                resultImage.at<uchar>(y, x) = 255 - rotatedImage.at<uchar>(y, x);
            }
            else {
                // Gamma transformation with gamma = 10
                resultImage.at<uchar>(y, x) = saturate_cast<uchar>(pow(rotatedImage.at<uchar>(y, x) / 255.0, 10) * 255.0);
            }
        }
    }

    // Display the input and result images
    namedWindow("Gray Image", WINDOW_AUTOSIZE);
    namedWindow("Result", WINDOW_AUTOSIZE);

    imshow("Gray Image", grayImage);
    imshow("Result", resultImage);

    // Wait for a key press indefinitely
    waitKey(0);

    return 0;
}
