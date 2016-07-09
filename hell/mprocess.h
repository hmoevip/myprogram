#ifndef MPROCESS_H
#define MPROCESS_H
#include <mycvheader.h>

class MProcess
{
public:
    MProcess();
    void colorReduce4(const cv::Mat &image, cv::Mat &result, int);
    void chooseBlue(const Mat &image,Mat &result,int col[3]);
    Mat findRect(const Mat &moriginal,const Mat &image,Mat &out);
    void drawDetectLines(Mat& image,const vector<Vec4i>& lines,const Scalar & color);
    Mat detectLine(Mat& image);
    Mat selectColor(const Mat &image);
    Mat drawHist(const Mat &image);
};

#endif // MPROCESS_H
