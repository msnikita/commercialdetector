#ifndef CLICKWINDOW_H
#define CLICKWINDOW_H

#include <QWidget>
#include <qobject.h>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE
class Click : public QMainWindow
{
    Q_OBJECT
    public:
    Click(QWidget *parent = 0);

    public slots:
    void openfile();
};
#endif // CLICKWINDOW_H
