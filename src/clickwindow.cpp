#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtGui>
#include <QApplication>
#include "clickwindow.h"

Click::Click(QWidget *parent): QMainWindow(parent)
{
    //Click:: openfile();

}
void Click::openfile()
{

     QTableView *mytable = new QTableView();
     QStandardItemModel *mytablemodel = new QStandardItemModel();
     mytablemodel->setRowCount(0);
     //mytablemodel->setHeaderData(Name);
    int Max_num_of_Columns(2);
    int Max_Number_of_Lines(0);
    mytablemodel->setColumnCount(Max_num_of_Columns);
    mytablemodel->setHeaderData(0, Qt::Horizontal, QObject::tr("Counter"));
    mytablemodel->setHeaderData(1, Qt::Horizontal, QObject::tr("Commercial"));
    QFile file("/home/admin123/output.txt");

   if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        qDebug() << "Error opening file";

    QTextStream InputDataFile(&file);
    while (!InputDataFile.atEnd())
    {

        QString line = InputDataFile.readLine();
        QStringList fields = line.split(" ");

        if (fields.size() == Max_num_of_Columns)
        {
            for (int column=0; column< Max_num_of_Columns; column++)
            {
                QStandardItem *item = new QStandardItem(fields[column]);
                mytablemodel->setItem(Max_Number_of_Lines, column, item);
            }
            Max_Number_of_Lines++ ;
        }
    }
    file.close();
    mytable->setWindowTitle("Detected Ads");
    mytable->setModel(mytablemodel);

    mytable->setGeometry(100,180,400,500);
    mytable->show();
}
