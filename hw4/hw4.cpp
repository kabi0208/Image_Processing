#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat sobel(Mat image){ // convolution

    double result = 0;
    int counter = 0;
    Mat SobelImage = image.clone();// copy
    for (int i = 1; i < image.rows - 1; i++){
        double mask[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
        for (int j = 1; j < image.cols - 1; j++){
            for(int m = 0; m < 3; m++){
                for (int k = i - 1; k < i + 2; k++){
                    for (int l = j - 1; l < j + 2; l++){
                        result += mask[counter] * image.at<Vec3b>(k, l)[m];
                        counter++;
                    }
                }
                // make the result in range 0 ~ 255
                if(result > 255)
                    result = 255;
                if(result < 0)
                    result *= -1;
                SobelImage.at<Vec3b>(i, j)[m] = result;// put the result into new image
                result = 0;
                counter = 0;
            }
        }
    }

    for (int i = 1; i < image.rows - 1; i++){
        double mask[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
        for (int j = 1; j < image.cols - 1; j++){
            for(int m = 0; m < 3; m++){
                for (int k = i - 1; k < i + 2; k++){
                    for (int l = j - 1; l < j + 2; l++){
                        result += mask[counter] * image.at<Vec3b>(k, l)[m];
                        counter++;
                    }
                }
                if(result < 0)
                    result *= -1;
                // make the result in range 0 ~ 255
                if(SobelImage.at<Vec3b>(i, j)[m] + result > 255)
                    result = 255 - SobelImage.at<Vec3b>(i, j)[m];
                SobelImage.at<Vec3b>(i, j)[m] += result;// put the result into new image
                result = 0;
                counter = 0;
            }
        }
    }
    return SobelImage;
}

int main(int argc, char *argv[]) {
    // read and display the image
    if(!argv[1]){
        printf("You haven't enter the file name of picture");
        return 0;
    }

    Mat image = imread(argv[1]);

    namedWindow("original image");
    imshow("original image", image);

    Mat sobelimage = (sobel(image)).clone();
    namedWindow("Sobel image");
    imshow("Sobel image", sobelimage);

    waitKey();
    return 0;
}
