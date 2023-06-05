#include <QApplication>
#include <QtWidgets>
#include <QLayout>
#include <QList>
#include <QPushButton>
#include "widget.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
