#include "opencv_hw/ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    // // PROBLEM 1
    // imshow("result", _frame);

    // // PROBLEM 2: B
    // imshow("B", _chans[0]);

    // // PROBLEM 2: G
    // imshow("G", _chans[1]);

    // // PROBLEM 2: R
    // imshow("R", _chans[2]);

    // // PROBLEM 3: Blue Subtraction
    // imshow("Blue Subtraction", _b_subtract);

    // // PROBLEM 3: Blue Thresholding
    // imshow("Blue Thresholding", _b_thresh);

    // // PROBLEM 3: Blue Mask
    // imshow("Blue Mask", _b_contour_mask);

    // // PROBLEM 3: Blue Result
    // imshow("Blue Result", _b_result);

    // // PROBLEM 4: Green Subtraction
    // imshow("Green Subtraction", _g_subtract);

    // // PROBLEM 4: Green Thresholding
    // imshow("Green Thresholding", _g_thresh);

    // // PROBLEM 4: Green Mask
    // imshow("Green Mask", _g_contour_mask);

    // // PROBLEM 4: Green Result
    // imshow("Green Result", _g_result);

    // // PROBLEM 5: Red Subtraction
    // imshow("Red Subtraction", _r_subtract);

    // // PROBLEM 5: Red Thresholding
    // imshow("Red Thresholding", _r_thresh);

    // // PROBLEM 5: Red Mask
    // imshow("Red Mask", _r_contour_mask);

    // // PROBLEM 5: Red Result
    // imshow("Red Result", _r_result);

    // // PROBLEM 6: All Three Cups
    // imshow("All Three Cups", _bgr_result);
}

void ColorFilter::findBlue() {
    subtract(_chans[0], _chans[2], _b_subtract);

    threshold(_b_subtract, _b_thresh, 50, 255, THRESH_BINARY);

    vector<Mat> contours;
    vector<Vec4i> hierarchy;

    findContours(_b_thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255, 255, 255),
        cv::LineTypes::FILLED, 8, hierarchy);

    _b_contour_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_b_contour_mask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    _b_result = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(_b_result, _b_contour_mask);
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[0], _g_subtract);

    threshold(_g_subtract, _g_thresh, 50, 255, cv::THRESH_BINARY);

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(_g_thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255, 255, 255),
        cv::LineTypes::FILLED, 8, hierarchy);

    _g_contour_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_g_contour_mask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    _g_result = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(_g_result, _g_contour_mask);
}

void ColorFilter::findRed() {
    subtract(_chans[2], _chans[1], _r_subtract);

    threshold(_r_subtract, _r_thresh, 50, 255, cv::THRESH_BINARY);

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(_r_thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(contourimage, contours, maxSizeContour, cv::Scalar(255, 255, 255),
        cv::LineTypes::FILLED, 8, hierarchy);

    _r_contour_mask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_r_contour_mask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    _r_result = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    _frame.copyTo(_r_result, _r_contour_mask);
}

void ColorFilter::findBGR() {
    cv::Mat b_and_g;
    bitwise_or(_b_result, _g_result, b_and_g);
    _bgr_result = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    bitwise_or(b_and_g, _r_result, _bgr_result);
}

cv::Mat ColorFilter::getBlueImage() {
    return _b_result;
}

cv::Mat ColorFilter::getGreenImage() {
    return _g_result;
}

cv::Mat ColorFilter::getRedImage() {
    return _r_result;
}

cv::Mat ColorFilter::getBGRImage() {
    return _bgr_result;
}


