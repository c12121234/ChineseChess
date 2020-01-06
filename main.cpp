#include "mainwindow.h"
#include "choosemode.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseMode* c = new ChooseMode;
    c->setWindowFlag(Qt::WindowMinimizeButtonHint);
    c->show();
    QObject::connect(c,&ChooseMode::destroyed,c,&ChooseMode::deleteLater);
    //ChooseMainWindow cm(c.m_nChoose);
    return a.exec();
}
