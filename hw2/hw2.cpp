#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat Image_Sharpening(Mat image, double mask[9]){ // convolution
    double result = 0;
    int counter = 0;
    Mat SharpeningImage = image.clone();// copy
    for (int i = 1; i < image.rows - 1; i++){
        for (int j = 1; j < image.cols - 1; j++){
            for (int k = i - 1; k < i + 2; k++){
                for (int l = j - 1; l < j + 2; l++){
                    result += mask[counter] * image.at<uchar>(k, l);
                    counter++;
                }
            }
            // make the result in range 0 ~ 255
            if(result > 255)
                result = 255;
            if(result < 0)
                result = 0;
            SharpeningImage.at<uchar>(i, j) = result;// put the result into new image
            result = 0;
            counter = 0;
        }
    }
    return SharpeningImage;
}

int main(int argc, char *argv[]) {
    // read and display the image
    if(!argv[1]){
        printf("You haven't enter the file name of picture");
        return 0;
    }

    Mat image = imread(argv[1], IMREAD_GRAYSCALE);

    namedWindow("original image");
    imshow("original image", image);

    double laplace_mask[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
    double high_boost_filtering[9] = {0, -1, 0, -1, 5.5, -1, 0, -1, 0};
    for(int i = 0; i < 9; i++){ // 5.5 = > 4 + A, A == 1.5;
        high_boost_filtering[i] /= 1.5; // let the total keep balance (not too bright or dark)
    }

    // build and display sharpening image of Laplacian operator
    Mat laplace = (Image_Sharpening(image, laplace_mask)).clone(); // copy image
    namedWindow("Laplacian image");
    imshow("Laplacian image", laplace);

    // build and display sharpening image of high boost filtering
    Mat high_boost = (Image_Sharpening(image, high_boost_filtering)).clone(); // copy image
    namedWindow("high boost image");
    imshow("high boost image", high_boost);

    waitKey();
    return 0;
}
