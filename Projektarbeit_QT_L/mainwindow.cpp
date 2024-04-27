#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGui>
#include "helpfunctions.h"
#include "helpfunctions_c.h"
#include "rapidcsv.h"
#include "messpunkt.h"
#include <vector>

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
