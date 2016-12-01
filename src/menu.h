#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui{
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    void paintEvent(QPaintEvent *pe);

private:
    Ui::Menu *uiMenu;

public slots:
    void addlogo();
    void addetect();
    void goback();
};

#endif // MENU_H
