#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

namespace Ui {
class welcome;
}

class welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();


private:
    Ui::welcome *uiwelcome;

public slots:
    void gonext();

};

#endif
