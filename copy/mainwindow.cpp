#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "helpfunctions.h"
#include "rapidcsv.h"
#include "messpunkt.h"
#include <vector>
#include <boost/circular_buffer.hpp>
#include <iostream>
#include <unistd.h>


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

void MainWindow::print_slot(double x, double y, double z)
{
  ui->lcdNumber_x->display(x);
  ui->lcdNumber_y->display(y);
  ui->lcdNumber_z->display(z);
}

void MainWindow::state_slot(bool state)
{
  QPalette palette;
  if(state==true){
      palette.setColor(QPalette::Base,Qt::green);
    }else{
      palette.setColor(QPalette::Base,Qt::red);
    }
  ui->lineEdit_2->setPalette(palette);
}

void MainWindow::receive_slot(int counter)
{
   ui->lineEdit_3->setFontPointSize();
   ui->lineEdit_3->setText(QString::number(counter));
}

void MainWindow::on_pushButton_clicked()
{
  QString s=ui->lineEdit->text();
  QByteArray ba = s.toLatin1();
  const char *path= ba.data();
  //const char *path="/home/timohin/Documents/Messpunkte_csv2.csv" ;
  std::vector<messpunkt> mpl=csv_einlesen(path);
  for(size_t i=0; i<mpl.size(); ++i){
      mpl[i].anzeigen();
    }
}

