#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGui>
#include "helpfunctions.h"
#include "helpfunctions_c.h"
#include "rapidcsv.h"

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
  rapidcsv::Document doc(path,rapidcsv::LabelParams(0,0));
  int rows= doc.GetRowCount();
  int cols= doc.GetColumnCount();
  /**
  float ** matrix=aufbau_matrix(rows,cols);
  csv_einlesen(path,matrix);
  print_array_2D(matrix,rows,cols);
  abbau_matrix(matrix,rows);
  */
}
