#ifndef PRINTER_H
#define PRINTER_H

#include <QMainWindow>
#include <QObject>

class printer: public QObject
{
  Q_OBJECT;
signals:
  void print_signal(double x,double y,double z);
  void state_signal(bool state);
  void receive_signal(int counter);
public:
  void print_values(double x,double y ,double z);
  void set_state(bool state);
  void receive_data(int counter);
  printer(){}
};

#endif // PRINTER_H
