#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcome.h"
#include "ui_welcome.h"
#include "menu.h"
#include "ui_menu.h"
#include "ui_addlogo1.h"
#include "admin.h"
#include "addlogo1.h"
#include <QtGui>


Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    uiMenu(new Ui::Menu)
{
    uiMenu->setupUi(this);
    uiMenu->back->setPalette(QPalette("/home/admin123/backwardbutton.png"));
     connect(uiMenu->detectad,SIGNAL(clicked()),this,SLOT(addetect()));
     connect(uiMenu->addlogo,SIGNAL(clicked()),this,SLOT(addlogo()));
     connect(uiMenu->cancle,SIGNAL(clicked()),this,SLOT(close()));
     connect(uiMenu->back,SIGNAL(clicked()),this,SLOT(goback()));
}

Menu::~Menu()
{
    delete uiMenu;
}
void Menu::addetect()
{
    MainWindow *ad=new MainWindow();
    this->hide();
    ad->setGeometry(500,500,1350,700);
    ad->setStyleSheet("background-image:url(/home/admin123/background.png);");
    ad->show();

}
void Menu::addlogo()
{
    Addlogo1 *adm=new Addlogo1();
    this->hide();
    adm->setGeometry(500,500,1350,700);
    adm->setStyleSheet("background-image:url(/home/admin123/background.png);");
    adm->show();
}
void Menu::goback()
{
    this->hide();
    welcome *w=new welcome();
    w->setGeometry(500,500,1350,700);
    w->setStyleSheet("background-image:url(/home/admin123/background.png);");
    w->show();
}
void Menu::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
