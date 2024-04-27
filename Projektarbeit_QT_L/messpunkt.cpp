#include "messpunkt.h"

messpunkt::messpunkt(float tx=0,float ty=0,float tz=0,float rx=0,float ry=0,float rz=0)
  :transx(tx),transy(ty),transz(tz),rotx(rx),roty(ry),rotz(rz){}

messpunkt::~messpunkt(){}
void messpunkt::anzeigen(){

  //std::cout <<transx<<" : " <<transy<<" : "<<transz<<"\n";
  //std::cout <<rotx<<" : " <<roty<<" : "<<rotz<<"\n";
  qDebug() <<transx<<" : " <<transy<<" : "<<transz<<"\n";
  //qDebug() <<rotx<<" : " <<roty<<" : "<<rotz<<"\n";

}
