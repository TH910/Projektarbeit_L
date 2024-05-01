#include "mainwindow.h"
#include <QApplication>
#include <QLocale>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  std::setlocale(LC_ALL,"en_US.UTF-8");
  w.show();

  return a.exec();
}
