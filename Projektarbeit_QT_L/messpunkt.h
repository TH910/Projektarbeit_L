#ifndef MESSPUNKT_H
#define MESSPUNKT_H

#include <iostream>
#include <QDebug>

class messpunkt
{
private:
//Position der Spitze
  float sx;
  float sy;
  float sz;
//Orientierung der Spitze als Rotationsmatrix
  float b0;
  float b1;
  float b2;
  float b3;
  float b4;
  float b5;
  float b6;
  float b7;
  float b8;
public:
  //Konstruktor
  messpunkt(float tx,float ty,float tz,float r0,float r1,float r2,float r3,float r4,float r5,float r6,float r7,float r8);
  messpunkt(float tx,float ty,float tz);
  messpunkt(char *stream);
  //Destruktor
  ~messpunkt();
  // printed alle Werte der Klasse
   void anzeigen();
};


#endif // MESSPUNKT_H
