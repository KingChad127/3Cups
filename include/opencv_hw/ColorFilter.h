#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat _b_subtract;
    cv::Mat _b_thresh;
    cv::Mat _b_contour_mask;
    cv::Mat _b_result;
    cv::Mat _g_subtract;
    cv::Mat _g_thresh;
    cv::Mat _g_contour_mask;
    cv::Mat _g_result;
    cv::Mat _r_subtract;
    cv::Mat _r_thresh;
    cv::Mat _r_contour_mask;
    cv::Mat _r_result;
    cv::Mat _bgr_result;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();

    cv::Mat getBlueImage();
    cv::Mat getGreenImage();
    cv::Mat getRedImage();
    cv::Mat getBGRImage();
};

#endif