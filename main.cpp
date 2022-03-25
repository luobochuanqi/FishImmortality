#include "mainw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainW w;
    w.show();
    w.setWindowTitle("摸鱼大陆-挂机修仙");
    w.setWindowIcon(QIcon(":/ico.ico"));
    return a.exec();
}
