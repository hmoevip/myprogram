#ifndef MAT_QIMAGE_H
#define MAT_QIMAGE_H
#include <mycvheader.h>

class Mat_Qimage
{
public:
    Mat_Qimage();
    static QImage cvMat2QImage(const cv::Mat& mat);
    static Mat QImage2cvMat(QImage image);
};

#endif // MAT_QIMAGE_H
