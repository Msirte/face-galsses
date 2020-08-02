#include "face.h"

MtcnnDetector mtcnn("../models-mtcnn");
Recognize recognize("../models-mobilefacenet/");


Mat getwarpAffineImg(Mat &src, vector<Point2f> &landmarks)
{
    Point2f eyesCenter = Point2f((landmarks[0].x + landmarks[1].x) * 0.5f, (landmarks[0].y + landmarks[1].y) * 0.5f);

    double dy = (landmarks[1].y - landmarks[0].y);
    double dx = (landmarks[1].x - landmarks[0].x);
    double angle = atan2(dy, dx) * 180.0 / CV_PI;

    Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, 1.0);
    Mat rot;

    warpAffine(src, rot, rot_mat, src.size());
    return rot;
}

Mat mt(Mat frame)
{
    Mat face_area, affined_area;

    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(frame.data, ncnn::Mat::PIXEL_BGR2RGB, frame.cols, frame.rows);
    
    // clock_t start, finish;
    // start = clock();
    vector<FaceInfo> finalBbox = mtcnn.Detect(ncnn_img);

    if (finalBbox.empty())
        return face_area;
    // finish = clock();
    // cout << "mtcnn cost " << (float)(finish - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    const int num_box = finalBbox.size();
    vector<Rect> bbox;
    vector<Point2f> point;
    bbox.resize(num_box);
    for (int i = 0; i < num_box; i++) {
        bbox[i] = Rect(finalBbox[i].x[0], finalBbox[i].y[0], finalBbox[i].x[1] - finalBbox[i].x[0], finalBbox[i].y[1] - finalBbox[i].y[0]);
    }

    point.push_back(Point2f(finalBbox[0].landmark[0], finalBbox[0].landmark[1]));
    point.push_back(Point2f(finalBbox[0].landmark[2], finalBbox[0].landmark[3]));

    affined_area = getwarpAffineImg(frame, point);
    face_area = affined_area(bbox[0]);

    return face_area;
}

vector<float> extract_feature(Mat img)
{
    vector<float> feature;
    recognize.start(img, feature);

    return feature;
}