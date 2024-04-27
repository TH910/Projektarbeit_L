#ifndef MESSPUNKT_H
#define MESSPUNKT_H

#include <iostream>
#include <QDebug>

class messpunkt
{
private:
  float transx;
  float transy;
  float transz;
  float rotx;
  float roty;
  float rotz;
public:
  //Konstruktor
  messpunkt(float tx,float ty,float tz,float rx,float ry,float rz);
  //Destruktor
  ~messpunkt();
   void anzeigen();
};


#endif // MESSPUNKT_H
