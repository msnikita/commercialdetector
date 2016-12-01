#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcome.h"
#include "ui_welcome.h"
#include "menu.h"
#include "admin.h"
#include "addlogo1.h"
#include "ui_admin.h"
#include "ui_menu.h"
#include <QtGui>


Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    uiAdmin(new Ui::Admin)
{
    uiAdmin->setupUi(this);
     connect(uiAdmin->pushButton,SIGNAL(clicked()),this,SLOT(addlogo()));

     //connect(uiAdmin->addlogo,SIGNAL(clicked()),this,SLOT(addlogo()));
}

Admin::~Admin()
{
    delete uiAdmin;
}

void Admin::addlogo()
{
    Addlogo1 *m=new Addlogo1();
    m->show();
}


