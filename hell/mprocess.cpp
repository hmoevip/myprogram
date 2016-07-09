#include "mprocess.h"

MProcess::MProcess()
{

}
Mat MProcess::drawHist(const Mat &image)
{
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = { 0, 256 };
    const float* ranges[] = { range};
    MatND hist;
    int channels[] = {0};

    calcHist( &image, 1, channels, Mat(), // do not use mask
          hist, 1, hist_size, ranges,
          true, // the histogram is uniform
          false );

    //根据灰度直方图，计算出灰度值最多的点
    //vector <int> dk;
    //float mk = 0;
    Point m_max,m_min;
    double max_val;
    minMaxLoc(hist, 0, &max_val, &m_min, &m_max);

 /*       for(int m_t=0;m_t<256;m_t++)
        {
            mk += hist.at<float>(m_t);
        }
        mk /= 255;
        bool flag = true;
        dk.push_back(-1);
        for(int m_t=0;m_t<256;m_t++)
        {
            if(flag)
            {
                if((mk - hist.at<float>(m_t)) < 0)
                {
                    flag = false;
                    //dk.push_back(m_t-10);
                    dk.push_back(m_t);
                }
            }else
            {
                if((mk - hist.at<float>(m_t)) > 0)
                {
                    flag = true;
                    //dk.push_back(m_t-10);
                    dk.push_back(m_t);
                }
            }
        }
        dk.push_back(256);

        //mDraw(result);
        //imshow( "Source", result );


         minMaxLoc(hist, 0, &max_val, 0, 0);*/
    int scale = 2;
    int hist_height=256;
    Mat hist_img = Mat::zeros(hist_height,bins*scale, CV_8UC3);
    for(int i=0;i<bins;i++)
    {
          float bin_val = hist.at<float>(i);
          int intensity = cvRound(bin_val*hist_height/max_val);  //要绘制的高度
          rectangle(hist_img,Point(i*scale,hist_height-1),
          Point((i+1)*scale - 1, hist_height - intensity),
          CV_RGB(255,255,255));
     }
    return hist_img;
}
Mat MProcess::selectColor(const Mat &image)
{
    Mat out;
    out = image;
    int nr= image.rows; // number of rows
    int nc= image.cols;// * image.channels(); // total number of elements per line

    Mat result(image.size(),CV_8U,Scalar(0));
    int step= result.step; // effective width
    uchar *data= result.data;
    uchar *data2 = image.data;
    int step2 = image.step;
    for (int j=0; j<nr; j++) {
        for (int i=0; i<nc; i++) {
            //蓝色最深
            if( *(data2+3*i)<200 && *(data2+3*i) >90)
                if( *(data2+3*i+1)>0 && *(data2+3*i+1)<150)
                    if( *(data2+3*i+2)>=0 && *(data2+3*i+2)<40)
                        *(data+i) = 255;
            //蓝色较深
            if( *(data2+3*i)<230 && *(data2+3*i) >180)
                if( *(data2+3*i+1)>0 && *(data2+3*i+1)<150)   //60,150
                    if( *(data2+3*i+2)>=0 && *(data2+3*i+2)<40)
                        *(data+i) = 0;
            //正常蓝色
            if( *(data2+3*i) >230)
                if( *(data2+3*i+1)>0 && *(data2+3*i+1)<150)   //78,80
                    if( *(data2+3*i+2)>=0 && *(data2+3*i+2)<40)
                        *(data+i) = 0;
            //黑色斑点
            if( *(data2+3*i)<90)
                if( *(data2+3*i+1)>0 && *(data2+3*i+1)<100)
                    if( *(data2+3*i+2)>0 && *(data2+3*i+2)<100)
                        *(data+i) = 0;
//            *(data+i) = *(data2+3*i)*0.5+*(data2+3*i+1)*0.5+*(data2+3*i+2)*0;
/*            for(int p=0; p<dk.size()-1; p++)
            {
                if(*(data+i)>dk[p] && *(data+i)<=dk[p+1])
                    *(data+i)= (255/dk.size()-1)*p;
            }
 /*           if(*(data+i)>=58 && *(data+i)<80)
                *(data+i)= 255;
            else if(*(data+i)>=80 && *(data+i)<=90)
                *(data+i)= 0;
            else if(*(data+i)>=90 && *(data+i)<=255)
                *(data+i)= 255;
            else if(*(data+i)>=0 && *(data+i)<58)
                *(data+i)= 255;
 /*           else if(*(data+i)>(m_max.y+20) && *(data+i)<(m_max.y+70))
                *(data+i)= 100;
            else if(*(data+i)>(m_max.y+70) && *(data+i)<(m_max.y+120))
                *(data+i)= 50;
            else
                *(data+i)= 0;*/
          } // end of row
          data+= step;  // next line
          data2+=step2;
    }
    //获取轮廓
    std::vector < std::vector <Point> > contours;
    //获取轮廓：
    findContours(result,         //图像
        contours,               //轮廓点
                        //包含图像拓扑结构的信息（可选参数，这里没有选）
        CV_RETR_CCOMP,           //获取轮廓的方法（这里获取外围轮廓）
        CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）

    drawContours(out,contours,-1,Scalar(0,255,255),2);

    Mat result2(image.size(),CV_8U,Scalar(0));
    data= result2.data;
    data2 = image.data;
    step = result.step;
    for (int j=0; j<nr; j++) {
        for (int i=0; i<nc; i++) {
            //蓝色较深
            if( *(data2+3*i)<230 && *(data2+3*i) >180)
                if( *(data2+3*i+1)>0 && *(data2+3*i+1)<150)   //60,150
                    if( *(data2+3*i+2)>=0 && *(data2+3*i+2)<40)
                        *(data+i) = 255;
          } // end of row
          data+= step;  // next line
          data2+=step2;
    }
    //获取轮廓
    contours.clear();
    //获取轮廓：
    findContours(result2,         //图像
        contours,               //轮廓点
                        //包含图像拓扑结构的信息（可选参数，这里没有选）
        CV_RETR_CCOMP,           //获取轮廓的方法（这里获取外围轮廓）
        CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）

    drawContours(out,contours,-1,Scalar(0,0,255),2);

    Mat result3(image.size(),CV_8U,Scalar(0));
    data= result3.data;
    step = result3.step;
    data2 = image.data;
    for (int j=0; j<nr; j++) {
        for (int i=0; i<nc; i++) {
            //黑色斑点
            if( *(data2+3*i)<90)
                if( *(data2+3*i+1)>=0 && *(data2+3*i+1)<100)
                    if( *(data2+3*i+2)>=0 && *(data2+3*i+2)<100)
                        *(data+i) = 255;
          } // end of row
          data+= step;  // next line
          data2+=step2;
    }
    //获取轮廓
    contours.clear();
    //获取轮廓：
    findContours(result3,         //图像
        contours,               //轮廓点
                        //包含图像拓扑结构的信息（可选参数，这里没有选）
        CV_RETR_CCOMP,           //获取轮廓的方法（这里获取外围轮廓）
        CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）

    drawContours(out,contours,-1,Scalar(0,255,0),2);
    //imshow( "Gray Histogram", out );
    return out;
}
Mat MProcess::findRect(const Mat &moriginal,const Mat &image,Mat &out)
{
    Mat mgrey,mthr;
    cvtColor(image,mgrey, CV_BGR2GRAY);
    //threshold(mgrey, mthr, 50, 255, CV_THRESH_BINARY_INV);
    int blockSize = 225;
    int constValue = 10;
    //二值
    adaptiveThreshold(mgrey, mthr, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
    //边缘
    //Canny(mgrey,mthr,50,150,3);
    //imshow("原图", im2);
    //Mat_Qimage::colorReduce4(mthr,mthr,64);
    //获取轮廓
    std::vector < std::vector <Point> > contours;
    //获取轮廓：
    findContours(mthr,         //图像
        contours,               //轮廓点
                        //包含图像拓扑结构的信息（可选参数，这里没有选）
        CV_RETR_EXTERNAL,           //获取轮廓的方法（这里获取外围轮廓）
        CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）

    //找到最大轮廓
    Mat result(mthr.size(),CV_8U,Scalar(255));
    //result = mthr;
    std::vector < std::vector <Point> >::const_iterator itc = contours.begin();
    while(itc != contours.end()-1)
    {
        if((*itc).size() <= (*(itc+1)).size())
            contours.erase(itc);
        else
        {
            contours.erase(itc+1);
        }
    }
    //画出轮廓，参数为：画板，轮廓，轮廓指示（这里画出所有轮廓），颜色，线粗
    //drawContours(result,contours,-1,Scalar(0),2);
    Rect r = boundingRect(Mat(contours[0]));
    //绘制矩形
    //rectangle(result, r, Scalar(0), 2);
    vector <Point> poly;

    approxPolyDP(Mat(contours[0]), poly, 1000, true);
 /*   vector<Point>::const_iterator itp = poly.begin();
    while (itp != (poly.end() - 1))
    {
        line(result, *itp, *(itp + 1), Scalar(0), 2);
        ++itp;
    }
    line(result, *itp, *(poly.begin()), Scalar(0), 2);*/


    //Rect r = boundingRect(Mat(contours[0]));
    RotatedRect calculatedRect;
    calculatedRect = minAreaRect(poly);
    //mmrect = cvMinAreaRect2(Mat(contours[0]),0);

    Point2f src[4];
    calculatedRect.points(src);
    //绘制最小矩形
    for (int i = 0; i < 4; i++)
        line(result, src[i], src[(i+1)%4], Scalar(0),2);
//    imshow("rectangles", result);
//    cvBoxPoints(calculatedRect,src);
//    line(result, src[0], src[1], Scalar(0), 2);
//    line(result, src[1], src[2], Scalar(0), 2);
//    line(result, src[2], src[3], Scalar(0), 2);
//    line(result, src[0], src[3], Scalar(0), 2);
   // src[0] = poly[0];
   // src[1] = poly[1];
   // src[2] = poly[2];
   // src[3] = poly[3];
    Point2f mto[4];
    mto[2] = Point2f(0,0);
    mto[1] = Point2f(0,r.height);
    mto[0] = Point2f(r.width,r.height);
    mto[3] = Point2f(r.width,0);

    Mat transform = getPerspectiveTransform(src,mto);



    Mat img_trans;// = Mat::zeros(moriginal.rows,moriginal.cols,CV_8UC3);
    warpPerspective(moriginal, img_trans, transform, img_trans.size(), INTER_LINEAR, BORDER_CONSTANT);
    Rect rect(0, 0, r.width, r.height);
    out = img_trans(rect);

    return result;
}

void MProcess::colorReduce4(const cv::Mat &image, cv::Mat &result, int div=64)
{
      int nr= image.rows; // number of rows
      int nc= image.cols;// * image.channels(); // total number of elements per line
      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //int step= image.step; // effective width
      result.create(image.rows,image.cols,image.type());
      // mask used to round the pixel value
      uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0
      // get the pointer to the image buffer
/*      uchar *data= image.data;
      for (int j=0; j<nr; j++) {
          for (int i=0; i<nc; i++) {
            *(data+i)= *data&mask + div/2;
            } // end of row
            data+= step;  // next line
      }*/
      //nc = nr * nc;
      for(int j=0; j<nr; j++)
      {
      uchar* data= result.ptr<uchar>(j);
      const uchar* idata= image.ptr<uchar>(j);
      for (int i=0; i<nc; i++) {
          *data++= (*idata++)&mask + div/2;
          *data++= (*idata++)&mask + div/2;
          *data++= (*idata++)&mask + div/2;
      }}
}

void MProcess::chooseBlue(const Mat &image,Mat &result,int col[3])
{
    int nr= image.rows; // number of rows
    int nc= image.cols * image.channels(); // total number of elements per line
    int istep= image.step; // effective width
    if (image.isContinuous())  {
              // then no padded pixels
              nc= nc*nr;
              nr= 1;  // it is now a 1D array
    }
    //int step = nc;
    result.create(image.rows,image.cols,image.type());
    int ostep = result.step;
   //  get the pointer to the image buffer
    uchar *data= result.data;
    const uchar* idata= image.data;
    for (int j=0; j<nr; j++)
    {
        for (int i=0; i<nc; i=i+3)
        {
            if(*(idata+i)>col[0] && *(idata+i+1)<col[1] && *(idata+i+2)<col[2])
            {
                *(data+i)= *(idata+i);
                *(data+i+1)= *(idata+i+1);
                *(data+i+2)= *(idata+i+2);
            }
            else
            {
                *(data+i)= 255;
                *(data+i+1)= 255;
                *(data+i+2)= 255;
            }
        } // end of row
        data += ostep;  // next line
        idata += istep;
    }
}

void MProcess::drawDetectLines(Mat& image,const vector<Vec4i>& lines,const Scalar& color)
{
    // 将检测到的直线在图上画出来
    vector<Vec4i>::const_iterator it=lines.begin();
    while(it!=lines.end())
    {
        Point pt1((*it)[0],(*it)[1]);
        Point pt2((*it)[2],(*it)[3]);
        line(image,pt1,pt2,color,2); //  线条宽度设置为2
        ++it;
    }
}

Mat MProcess::detectLine(Mat& image)
{
    int nr= image.rows;
    int nc= image.cols * image.channels();
    int istep= image.step;
    uchar* idata= image.data;
    QDebug deb = qDebug();
    int sum = 0;
    Mat result = Mat::zeros(image.rows,image.cols,image.type());
    int ostep = result.step;
    uchar* data= result.data;
    for (int j=0; j<nr; j++)
    {
        for (int i=0; i<nc; i++)
        {
           int b = *(idata+i);
           if(b==255)
               sum++;
           //deb.nospace() << sum;
        }
        if(sum>170 && sum <190)
        {
            for (int i=0; i<nc; i++)
            {
                if(*(idata+i)==255)
                {
                    *(data+i) = *(idata+i);
                    i += 5;
                }
            }
        }
        //deb.nospace() <<sum<< endl;
        sum = 0;
        idata += istep;
        data += ostep;
    }
    sum = 0;
    data= result.data;
    //int mtemp[100];
    //memset(mtemp,0,sizeof(mtemp));
    vector <int> rrow;
    vector <int> outn;
    int mtemp = 0;
    int sk = 0;
    vector <int> ccol;
    for(int j=0; j<nc; j++)
    {
        for(int k=0; k<nr; k++)
        {
            if(*(data+j+k*ostep)==255)
                break;
            if(k==nr-1)
            {
                ccol.push_back(j);
            }
        }
    }
    for(unsigned long q=0; q< ccol.size(); q++)
    {
        if( abs(ccol[q+1]-ccol[q]) <= 2 )
        {
            ccol.erase(ccol.begin()+q);
            q=0;
        }
    }
    for (int j=0; j<nr; j++)
    {
        for (int p=0; p<nc; p++)
        {
            if(*(data+p)==255)
                sum++;
            if(sum>90 && p==nc-1)
            {
                for(int i=0; i<nc; i++)
                {

                    if(*(data+i)==255)
                    {
                        unsigned long flag = 0;
                        int kk=0;
                        int ll=0;
                        if(i<ccol[0])
                            flag = 0;
                        for(unsigned long mm=1; mm<ccol.size();mm++)
                        {
                            if(i<ccol[mm] && i>ccol[mm-1])
                                flag = mm;
                        }
                        if(i>ccol[ccol.size()-1])
                            flag = ccol.size()-1;
                        for(int k=0; k<nr-j; k++)
                        {
                            int msum = 0;
                            if(flag == 0)
                            {
                                for(int s=0; s<ccol[flag]; s++)
                                {
                                    msum += *(data+k*ostep+s);
                                }
                            }else if(flag == ccol.size()-1)
                            {
                                for(int s=ccol[flag]; s<nc; s++)
                                {
                                    msum += *(data+k*ostep+s);
                                }
                            }else
                            {
                                int asd = ccol[flag]-ccol[flag-1];
                                for(int s=0; s<asd; s++)
                                {
                                    msum += *(data+k*ostep+s+ccol[flag-1]);
                                }
                            }
                         /*   for(int s=0;s<13;s++)
                            {
                                if(i+s-6<0 || i+s-6>=nc)
                                    msum += 0;
                                msum += *(data+k*ostep+i+s-6);
                            }*/
                                if(msum>=255)
                                {
                                    ll++;
                                    if(kk<=3 && ll>=3)
                                        kk=0;
                                }else
                                {
                                    if(ll<=3 && kk>=3)
                                        ll=0;
                                    kk++;
                                }
                                if(kk>3 && ll>3)
                                {
                                    mtemp++;
                                    rrow.push_back(k);
                                    kk = 0;
                                    ll=0;
                                }
                        }
                        deb.nospace() <<mtemp<<" ";
                        outn.push_back(mtemp);
                        mtemp = 0;
                    }
                }
                sk = j;
                j = nr+1;
                break;
            }
        }
        data += ostep;
    }
    qDebug()<<outn.size()<<endl;
    data= result.data;
    for(unsigned long t=0; t<rrow.size(); t++)
    {
       for(int p=0; p<nc; p++)
       {
           *(data+(rrow[t]+sk)*ostep+p) = 255;
       }
    }
    qDebug()<<ccol.size()<<endl;
    for(int p=0; p<nr; p++)
    {
       for(unsigned long t=0; t<ccol.size(); t++)   //如果这个值不够90以上，说明图像没校准好，竖线不够值
       {
           *(data+p*ostep+ccol[t]) = 255;
       }
    }
    return result;
}

