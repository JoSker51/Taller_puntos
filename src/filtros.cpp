#include "../include/filtros.h"
#include <cmath>
#include <algorithm>

static cv::Mat convolucion(const cv::Mat& img, const std::vector<std::vector<int>>& kernel)
{
    int k = kernel.size() / 2;
    cv::Mat resultado = cv::Mat::zeros(img.size(), CV_8U);

    for(int i = k; i < img.rows - k; i++)
    {
        for(int j = k; j < img.cols - k; j++)
        {
            int suma = 0;

            for(int ki = -k; ki <= k; ki++)
            {
                for(int kj = -k; kj <= k; kj++)
                {
                    int pixel = img.at<uchar>(i + ki, j + kj);
                    int peso = kernel[ki + k][kj + k];
                    suma += pixel * peso;
                }
            }

            suma = std::abs(suma);
            suma = std::min(255, suma);
            resultado.at<uchar>(i,j) = suma;
        }
    }

    return resultado;
}

cv::Mat edgesManual(const cv::Mat& img)
{
    cv::Mat res = cv::Mat::zeros(img.size(), CV_8U);

    for(int i = 1; i < img.rows - 1; i++)
    {
        for(int j = 1; j < img.cols - 1; j++)
        {
            int gx = img.at<uchar>(i,j+1) - img.at<uchar>(i,j-1);
            int gy = img.at<uchar>(i+1,j) - img.at<uchar>(i-1,j);

            int g = std::sqrt(gx*gx + gy*gy);
            res.at<uchar>(i,j) = std::min(255,g);
        }
    }

    return res;
}

cv::Mat sobelManual(const cv::Mat& img)
{
    std::vector<std::vector<int>> kernel =
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    return convolucion(img, kernel);
}

cv::Mat scharrManual(const cv::Mat& img)
{
    std::vector<std::vector<int>> kernel =
    {
        {-3,0,3},
        {-10,0,10},
        {-3,0,3}
    };

    return convolucion(img, kernel);
}

cv::Mat laplacianoManual(const cv::Mat& img)
{
    std::vector<std::vector<int>> kernel =
    {
        {0,1,0},
        {1,-4,1},
        {0,1,0}
    };

    return convolucion(img, kernel);
}

cv::Mat sobelMagnitudeManual(const cv::Mat& img)
{
    std::vector<std::vector<int>> sx =
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    std::vector<std::vector<int>> sy =
    {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    cv::Mat gx = convolucion(img, sx);
    cv::Mat gy = convolucion(img, sy);

    cv::Mat mag = cv::Mat::zeros(img.size(), CV_8U);

    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j++)
        {
            int v = std::sqrt(gx.at<uchar>(i,j)*gx.at<uchar>(i,j) +
                              gy.at<uchar>(i,j)*gy.at<uchar>(i,j));

            mag.at<uchar>(i,j) = std::min(255,v);
        }
    }

    return mag;
}

static cv::Mat gaussianManual(const cv::Mat& img)
{
    std::vector<std::vector<int>> kernel =
    {
        {1,2,1},
        {2,4,2},
        {1,2,1}
    };

    cv::Mat blur = convolucion(img, kernel);

    for(int i=0;i<blur.rows;i++)
        for(int j=0;j<blur.cols;j++)
            blur.at<uchar>(i,j) /= 16;

    return blur;
}

cv::Mat logManual(const cv::Mat& img)
{
    cv::Mat blur = gaussianManual(img);
    return laplacianoManual(blur);
}

cv::Mat cannyManual(const cv::Mat& img)
{
    cv::Mat blur = gaussianManual(img);

    std::vector<std::vector<int>> sx =
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    std::vector<std::vector<int>> sy =
    {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    cv::Mat gx = convolucion(blur, sx);
    cv::Mat gy = convolucion(blur, sy);

    cv::Mat edges = cv::Mat::zeros(img.size(), CV_8U);

    int low = 50;
    int high = 100;

    for(int i=0;i<img.rows;i++)
    {
        for(int j=0;j<img.cols;j++)
        {
            int g = std::sqrt(gx.at<uchar>(i,j)*gx.at<uchar>(i,j) +
                              gy.at<uchar>(i,j)*gy.at<uchar>(i,j));

            if(g > high)
                edges.at<uchar>(i,j) = 255;
            else if(g > low)
                edges.at<uchar>(i,j) = 100;
            else
                edges.at<uchar>(i,j) = 0;
        }
    }

    return edges;

}
 cv::Mat zeroCrossing(const cv::Mat& img)
    {
        cv::Mat result = cv::Mat::zeros(img.size(), CV_8U);

        for (int y = 1; y < img.rows - 1; y++)
        {
            for (int x = 1; x < img.cols - 1; x++)
            {
                float center = img.at<float>(y, x);
                bool edge = false;

                for (int j = -1; j <= 1; j++)
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        if (i == 0 && j == 0)
                            continue;

                        float neighbor = img.at<float>(y + j, x + i);

                        if (center * neighbor < 0)
                        {
                            edge = true;
                        }
                    }
                }

                if (edge)
                {
                    result.at<uchar>(y, x) = 255;
                }
            }
        }

        return result;
    }