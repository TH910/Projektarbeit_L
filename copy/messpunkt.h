#ifndef MESSPUNKT_H
#define MESSPUNKT_H

#include <iostream>
#include <QDebug>

class messpunkt
{
public:
  //Position der Spitze
  double sx;
  double sy;
  double sz;
  //Orientierung der Spitze als Rotationsmatrix
  double b0;
  double b1;
  double b2;
  double b3;
  double b4;
  double b5;
  double b6;
  double b7;
  double b8;

  //Konstruktor
  messpunkt();
  messpunkt(double tx,double ty,double tz,double r0,double r1,double r2,double r3,double r4,double r5,double r6,double r7,double r8);
  messpunkt(double tx,double ty,double tz);
  messpunkt(char *stream);
  //Destruktor
  ~messpunkt();
  // printed alle Werte der Klasse
  void anzeigen();
};


#endif // MESSPUNKT_H
