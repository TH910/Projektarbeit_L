#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  Ui::MainWindow *ui;
public slots:
  void print_slot(double x,double y,double z);
  void state_slot(bool state);
  void receive_slot(int counter);
private slots:
  void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
