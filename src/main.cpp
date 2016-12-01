#include <QtGui/QApplication>
#include "mainwindow.h"
#include "welcome.h"
#include <QtGui>
int x, y;
int screenWidth,screenHeight,WIDTH = 1350,HEIGHT = 700;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QPushButton *pushButton;
    welcome w;
    w.setWindowTitle("AD DETECTION");
    QDesktopWidget *desktop = QApplication::desktop();

      screenWidth = desktop->width();
      screenHeight = desktop->height();
      x = (screenWidth - WIDTH) / 2;
      y = (screenHeight - HEIGHT) / 2;
      w.setWindowIcon(QIcon("/home/admin123/gui/images/1.png"));
      w.setStyleSheet("background-image:url(/home/admin123/background.png);");
      w.show();
      w.setGeometry(x, y,WIDTH,HEIGHT+150);
    return a.exec();
}
