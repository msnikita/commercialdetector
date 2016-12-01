#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcome.h"
#include "ui_welcome.h"
#include "menu.h"
#include <QtGui>
#include <Qt>

welcome::welcome(QWidget *parent) :
    QMainWindow(parent),
    uiwelcome(new Ui::welcome)
{
    uiwelcome->setupUi(this);
    uiwelcome->next->
     connect(uiwelcome->next,SIGNAL(clicked()),this,SLOT(gonext()));
     connect(uiwelcome->cancle,SIGNAL(clicked()),this,SLOT(close()));
}

welcome::~welcome()
{
    delete uiwelcome;
}
void welcome::gonext()
{
    Menu *g=new Menu();
    this->hide();
    g->setGeometry(500,500,1350,700);
    g->setStyleSheet("background-image:url(/home/admin123/background3.jpeg);");
    g->show();
}
