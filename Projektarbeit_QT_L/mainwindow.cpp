#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGui>
#include "helpfunctions.h"
#include "helpfunctions_c.h"
#include "rapidcsv.h"
#include "messpunkt.h"
#include <vector>
#include <boost/circular_buffer.hpp>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  QString s=ui->lineEdit->text();
  QByteArray ba = s.toLatin1();
  const char *path= ba.data();
  //const char *path= "/home/timohin/Documents/Messpunkte_csv.csv";
  std::vector<messpunkt> mpl=csv_einlesen(path);
  for(size_t i=0; i<mpl.size(); ++i){
   mpl[i].anzeigen();
  }
}

void MainWindow::on_pushButton_2_clicked()
{
  udp_server();
}

void MainWindow::on_pushButton_3_clicked()
{

  char stream[]="fr 3823\nts 44597.741924\n6dcal 1\n6df2 1 1 [0 -1.000 8 3][0.000 0.000 0.000][0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000][0 0.00 0.00 0.00]\n6d 1 [0 1.000][84.203 37.681 172.102 99.1970 6.7130 9.6575][0.979069 0.086946 0.184021 -0.166608 -0.176923 0.970021 0.116897 -0.980377 -0.158734]\n3d 0\n6dmt2 1 1 [0 -1.000 1 0.000][1.777 2.777 3.777][0.888888 1.888888 2.888888 3.888888 4.888888 5.888888 6.888888 7.888888 8.888888][0][0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00]\n6dmtr 0 0\ngl 0 \nglcal 0 \0";
  messpunkt mptest(stream);
  mptest.anzeigen();


}
