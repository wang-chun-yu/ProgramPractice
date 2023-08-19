#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

// bilinear interpolation
template <typename T>
inline float GetPixelValue(const cv::Mat& img, float x, float y) {
    // boundary check
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= img.cols) x = img.cols - 1;
    if (y >= img.rows) y = img.rows - 1;
    const T* data = &img.at<T>(floor(y), floor(x));
    float xx = x - floor(x);
    float yy = y - floor(y);
    return float((1 - xx) * (1 - yy) * data[0] + xx * (1 - yy) * data[1] + (1 - xx) * yy * data[img.step / sizeof(T)] +
                 xx * yy * data[img.step / sizeof(T) + 1]);
}

// #define TEST1
#ifdef TEST1
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
    printf("No image data \n");
    return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
#endif

#define TEST2
#ifdef TEST2
int main(int argc, char** argv )
{
    // if ( argc != 2 )
    // {
    //     printf("usage: DisplayImage.out <Image_Path>\n");
    //     return -1;
    // }
    Mat image;
    // image = imread( argv[1], 1 );
     image = imread( "./1.jpg", 1 );
    Mat image_f;
    image.convertTo(image_f,CV_32FC1);
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    std::cout << "img.step:" << image.step << std::endl;
    std::cout << "img.cols:" << image.cols << std::endl;
    std::cout << "img.rows:" << image.rows << std::endl;
    std::cout << "GetPixelValue:" << GetPixelValue<float>(image,100,100) << std::endl;
    std::cout << "image:" << image << std::endl;
    std::cout << "image_f:" << image_f << std::endl;
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    namedWindow("Display Image_f", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    imshow("Display Image_f", image_f);
    waitKey(0);
    return 0;
}
#endif