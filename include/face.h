#include <vector>
#include <opencv2/opencv.hpp>
#include "mobilefacenet.h"
#include "mtcnn.h"

using namespace std;
using namespace cv;


Mat mt(Mat frame);
Mat getwarpAffineImg(Mat &src, vector<Point2f> &landmarks);
vector<float> extract_feature(Mat img);


