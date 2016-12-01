#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui{
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();

private:
    Ui::Admin *uiAdmin;

public slots:
    void addlogo();
};

#endif // ADMIN_H
