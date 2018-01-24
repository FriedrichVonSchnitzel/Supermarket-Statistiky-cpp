#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <math.h>
#include <QTimer>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
