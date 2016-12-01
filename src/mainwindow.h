#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "opencv2/highgui/highgui.hpp"
#include"opencv/cv.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/legacy.hpp"

#include <cv.h>

#include <ctype.h>
#include <stdio.h>

#include<string.h>
#include <iostream>
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CvCapture* capture;
    IplImage* frame;
    IplImage *image;
    double compareSURFDescriptors( const float* d1, const float* d2, double best, int length );
    int naiveNearestNeighbor( const float* vec, int laplacian,const CvSeq* model_keypoints,const CvSeq* model_descriptors );
    void findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, const CvSeq* imageDescriptors,vector<int>& ptpairs);
    
private:
    Ui::MainWindow *ui;
public slots:
    int surf();
    void output();
    void back();
    void start();
    void stop();
    void cancle();
};

#endif // MAINWINDOW_H
