#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcome.h"
#include "ui_welcome.h"
#include "addlogo1.h"
#include "ui_admin.h"
#include "menu.h"
#include "ui_addlogo1.h"
#include "ui_menu.h"
#include <QtGui>


Addlogo1::Addlogo1(QWidget *parent) :
    QMainWindow(parent),
    uiAddlogo1(new Ui::Addlogo1)
{
    uiAddlogo1->setupUi(this);
    connect(uiAddlogo1->addlogo,SIGNAL(clicked()),this,SLOT(showlogo()));
    connect(uiAddlogo1->back,SIGNAL(clicked()),this,SLOT(back()));
    connect(uiAddlogo1->cancel,SIGNAL(clicked()),this,SLOT(close()));
}

Addlogo1::~Addlogo1()
{
    delete uiAddlogo1;
}
void Addlogo1::showlogo()
{
    for(int i=1;i<4;i++)
    {
        char object_filename[100];
        sprintf(object_filename,"/home/admin123/logo/image%d.png", i);

    }
}
void Addlogo1::back()
{
    this->hide();
    Menu *m=new Menu();
    m->setGeometry(500,500,1350,700);
    m->setStyleSheet("background-image:url(/home/admin123/selectoption.png);");
    m->show();
}
void Addlogo1::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
