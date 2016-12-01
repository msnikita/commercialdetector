#include "mainwindow.h"
#include "clickwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <phonon/mediaobject.h>
#include <QPixmap>
#include <QString>
#include "menu.h"
#define max 30
using namespace std;
FILE *file;
typedef struct output
{
    char name[max];
    int cnt;
}output;
output op[max];
typedef struct input
{
    int no;
    char name[max];
}input;
input ip[max];
int op_cnt=0;
int ip_cnt=0;
static double dis;
int flag=0;
int adflag=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //ui->pushButton->QPushButton("Output");
    connect(ui->output,SIGNAL(clicked()),this,SLOT(output()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancle()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->back,SIGNAL(clicked()),this,SLOT(back()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::surf()
{
    FILE* fi = fopen("/home/admin123/input3.txt","r");
      int n;

      char line[100];
      for(int i=0;i<max;i++)
      {
          ip[i].no=0;
      }
       for( ip_cnt=0;fgets ( line, sizeof line, fi ) != NULL;ip_cnt++ ) /* read a line */
      {
          for(n=0;line[n]!=' ';n++)
          {
              int no=line[n]-48;
              ip[ip_cnt].no=(ip[ip_cnt].no*10)+no;
          }
          n++;
          int l=0;
          while(line[n]!='\n')
          {
              ip[ip_cnt].name[l]=line[n];
              //fputs ( line, stdout ); /* write the line */
              n++;
              l++;
          }
      }

  fclose(fi);
  for(int m=0;m<ip_cnt;m++)
      printf("%d %s",ip[m].no,ip[m].name);

      CvCapture* capture = cvCreateFileCapture("/home/admin123/ztv1.mp4");


      int count[10];

      for(int j=0;j<10;j++)
          count[j]=0;
      IplImage* frame;
     int adcounter=250;
      while(1)
      {

          if(adflag==1)
              break;
          for(int k=0;k<10;k++)
              frame = cvQueryFrame( capture );
          if(!frame)
              break;


                   cvSaveImage("/home/admin123/myFrame.png",frame);
                   cvNamedWindow("PROGRAM",CV_WINDOW_AUTOSIZE);
                   cv::moveWindow("PROGRAM",500,70);
                   cvShowImage("PROGRAM",frame);
                  const char* scene_filename ="/home/admin123/myFrame.png";
                  for (int i1 =1; i1 <= ip_cnt; i1++)
                 {

                     char object_filename[100];
                     sprintf(object_filename,"/home/admin123/logo/image%d.png", i1);


                      cv::initModule_nonfree();
                      CvMemStorage* storage = cvCreateMemStorage(0);
                      IplImage* object = cvLoadImage( object_filename, CV_LOAD_IMAGE_GRAYSCALE );
                      IplImage* image = cvLoadImage( scene_filename, CV_LOAD_IMAGE_GRAYSCALE );

                      if( !object || !image )
                      {
                          fprintf( stderr, "Can not load %s and/or %s\n"
                              "Usage: find_obj [<object_filename> <scene_filename>]\n",
                              object_filename, scene_filename );
                          exit(-1);
                      }
                      cvNamedWindow("GRAY",CV_WINDOW_AUTOSIZE);
                      cv::moveWindow("GRAY",1000,70);
                      cvShowImage("GRAY",image);
                      cvNamedWindow("LOGO",CV_WINDOW_AUTOSIZE);
                       cv::moveWindow("LOGO",1000,420);
                      cvShowImage("LOGO",object);
                      char c = cvWaitKey(33);
                      if( c == 27 ) break;
                      //cvWaitKey(0);

                      CvSeq *objectKeypoints = 0, *objectDescriptors = 0;
                      CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
                      CvSURFParams params = cvSURFParams(500, 1);//// Only values with a hessian greater than 500 are considered for keypoints

                     double tt = (double)cvGetTickCount();
                    cvExtractSURF( object, 0, &objectKeypoints, &objectDescriptors, storage, params );//finds robust features in the image
                    cvExtractSURF( image, 0, &imageKeypoints, &imageDescriptors, storage, params );

                     tt = (double)cvGetTickCount() - tt;

                    vector <int> ptpairs;

                    findPairs( objectKeypoints, objectDescriptors, imageKeypoints, imageDescriptors, ptpairs );
                      if(flag==1)
                      {
                          for(int n=0;n<ip_cnt;n++)
                          {

                              if(i1==ip[n].no)
                              {
                                  if(strcmp(ip[n].name,op[op_cnt-1].name)!=0)
                                  {
                                  strcpy(op[op_cnt].name,ip[n].name);
                                  count[i1]=count[i1]+1;
                                  op[op_cnt].cnt=count[i1];
                                  op_cnt++;
                                  }
                              }
                          }
                          printf("\n%d %s %d",op_cnt-1,op[op_cnt-1].name,op[op_cnt-1].cnt);
                          file = fopen("/home/admin123/output.txt", "w");
                          for (int i2 = 0; i2 < op_cnt; i2++)
                          {
                          fprintf(file,"%d %s\n",op[i2].cnt,op[i2].name );
                          }
                          fclose(file);
                          ui->label->setPixmap(QPixmap("/home/admin123/AD.png"));

                          adcounter=0;
                          break;
                      }
                      else
                      {
                          adcounter++;
                          if(adcounter>250)
                          {
                              ui->label->setPixmap(QPixmap("/home/admin123/program.png"));
                              adcounter=250;
                          }

                    }

  cvReleaseImage(&image);
  cvReleaseImage(&object);
  cvClearMemStorage(storage);
 }
  flag=0;
   }
  cvReleaseCapture( &capture );
  cvDestroyWindow("GRAY");
  cvDestroyWindow("LOGO");
  cvDestroyWindow("PROGRAM");

return 0;
}
double MainWindow::compareSURFDescriptors( const float* d1, const float* d2, double best, int length )
{
    double total_cost = 0;
    assert( length % 4 == 0 );
    for( int i = 0; i < length; i += 4 )
    {
        double t0 = d1[i] - d2[i];
        double t1 = d1[i+1] - d2[i+1];
        double t2 = d1[i+2] - d2[i+2];
        double t3 = d1[i+3] - d2[i+3];
        total_cost += t0*t0 + t1*t1 + t2*t2 + t3*t3;
/*
We are sending a total cost, that's slightly greater or smaller than the best

  */
      if( total_cost > best )
            break;
    }
    return total_cost;
}


int MainWindow::naiveNearestNeighbor( const float* vec, int laplacian,const CvSeq* model_keypoints,const CvSeq* model_descriptors )
{
    int length = (int)(model_descriptors->elem_size/sizeof(float));
    int i, neighbor = -1;
    double d, dist1 = 1e6, dist2 = 1e6;
    CvSeqReader reader, kreader;
    cvStartReadSeq( model_keypoints, &kreader, 0 );
    cvStartReadSeq( model_descriptors, &reader, 0 );

    for( i = 0; i < model_descriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* mvec = (const float*)reader.ptr;
     CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
        if( laplacian != kp->laplacian )
            continue;
        d = compareSURFDescriptors( vec, mvec, dist2, length );

        if( d < dist1 )
        {
            dist2 = dist1;
            dist1 = d;
            neighbor = i;
        }
        else if ( d < dist2 )
            dist2 = d;
    }
dis=dis+dist1;
    if ( dist1 < 0.6*dist2 )
        return neighbor;
    return -1;
}

void MainWindow::findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,const CvSeq* imageKeypoints, const CvSeq* imageDescriptors,vector<int>& ptpairs)
{
    int i;
    CvSeqReader reader, kreader;
    cvStartReadSeq( objectKeypoints, &kreader );
    cvStartReadSeq( objectDescriptors, &reader );
    ptpairs.clear();

    for( i = 0; i < objectDescriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* descriptor = (const float*)reader.ptr;
        CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
        int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors);

        if( nearest_neighbor >= 0 )
        {
            ptpairs.push_back(i);
            ptpairs.push_back(nearest_neighbor);
        }
    }

//printf("\n%lf\n",(dis/objectDescriptors->total));

if((dis/objectDescriptors->total)<=0.180)
{
    //printf("ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDdd");
    flag=1;
}
    dis=0;
}
void MainWindow::output()
{
    Click *click1=new Click();
     click1->openfile();
}
void MainWindow::back()
{
    this->hide();
    adflag=1;
    Menu *m=new Menu();
    m->show();
    m->setGeometry(500,500,1350,700);
    m->setStyleSheet("background-image:url(/home/admin123/background3.jpeg);");
    m->show();
}

void MainWindow::start()
{
    adflag=0;
    bool t=true;
    bool f=false;
    ui->stop->setEnabled(t);
   ui->start->setEnabled(f);
   ui->output->setEnabled(t);
    MainWindow *ad=new MainWindow;
     ad->surf();

}
void MainWindow::stop()
{
    adflag=1;
    ui->start->setEnabled(true);
}
void MainWindow::cancle()
{
    this->hide();
    adflag=1;

}
