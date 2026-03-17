#ifndef FILTROS_H
#define FILTROS_H

#include <opencv2/opencv.hpp>

cv::Mat edgesManual(const cv::Mat& img);
cv::Mat sobelManual(const cv::Mat& img);
cv::Mat scharrManual(const cv::Mat& img);
cv::Mat laplacianoManual(const cv::Mat& img);
cv::Mat sobelMagnitudeManual(const cv::Mat& img);
cv::Mat logManual(const cv::Mat& img);
cv::Mat cannyManual(const cv::Mat& img);
cv::Mat zeroCrossing(const cv::Mat& img);

#endif
