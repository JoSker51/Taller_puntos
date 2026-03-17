#include <opencv2/opencv.hpp>
#include <iostream>
#include "../include/filtros.h"

int main()
{
    cv::Mat img = cv::imread("../data/imagen.jpg");

    if(img.empty())
    {
        std::cout<<"Error cargando imagen\n";
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);

    int op;

    do
    {
        std::cout<<"\n--- MENU ---\n";
        std::cout<<"1 Edges\n";
        std::cout<<"2 Sobel\n";
        std::cout<<"3 Scharr\n";
        std::cout<<"4 Laplaciano\n";
        std::cout<<"5 Sobel Magnitude\n";
        std::cout<<"6 LoG\n";
        std::cout<<"7 Canny\n";
        std::cout<<"8 Zero Crossing\n";
        std::cout<<"0 Salir\n";

        std::cin>>op;

        cv::Mat resultado;

        switch(op)
        {
            case 1: resultado = edgesManual(gray); break;
            case 2: resultado = sobelManual(gray); break;
            case 3: resultado = scharrManual(gray); break;
            case 4: resultado = laplacianoManual(gray); break;
            case 5: resultado = sobelMagnitudeManual(gray); break;
            case 6: resultado = logManual(gray); break;
            case 7: resultado = cannyManual(gray); break;
            case 8: resultado = zeroCrossing(gray); break;

        }

        if(op!=0)
        {
            cv::imshow("Resultado",resultado);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }

    }while(op!=0);

    return 0;
}
