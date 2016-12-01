#ifndef ADDLOGO1_H
#define ADDLOGO1_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui{
class Addlogo1;
}

class Addlogo1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Addlogo1(QWidget *parent = 0);
    ~Addlogo1();
    void paintEvent(QPaintEvent *pe);

private:
    Ui::Addlogo1 *uiAddlogo1;

public slots:
    void showlogo();
    void back();
};

#endif // ADDLOGO1_H
