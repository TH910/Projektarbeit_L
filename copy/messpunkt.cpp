#include "messpunkt.h"

messpunkt::messpunkt(){}
messpunkt::messpunkt(double tx, double ty, double tz, double r0, double r1, double r2, double r3, double r4, double r5, double r6, double r7,double r8)
  :sx(tx),sy(ty),sz(tz),b0(r0),b1(r1),b2(r2),b3(r3),b4(r4),b5(r5),b6(r6),b7(r7),b8(r8){}

messpunkt::messpunkt(double tx,double ty, double tz): sx(tx), sy(ty), sz(tz),b0(0),b1(0),b2(0),b3(0),b4(0),b5(0),b6(0),b7(0),b8(0){}

messpunkt::messpunkt(char *stream){

  char extract_stream[250];
  char start[]= "6dmt2";
  char end[]= "6dmtr";

  char *ptrStart=strstr(stream,start);
  char *ptrEnd=strstr(stream,end);
  *ptrEnd='\0';
  strcpy(extract_stream,ptrStart);
  //printf("%s",extract_stream);
  char *pch;
  pch=strtok(extract_stream," []");
  int  num=0;
  int printon=0;
  double buf=0;
  while(pch!=NULL){

      switch(num) {
        case 7:
          buf=atof(pch);
          if(printon==1)printf("Float value of sx %f\n", buf);
          sx=buf;
          break;
        case 8:
          buf=atof(pch);
          if(printon==1)printf("Float value of sy %f\n",buf);
          sy=buf;
          break;
        case 9:
          buf=atof(pch);
          if(printon==1)printf("Float value of sz %f\n",buf);
          sz=buf;
          break;
        case 10:
          buf=atof(pch);
          if(printon==1)printf("Float value of b0 %f\n",buf);
          b0=buf;
          break;
        case 11:
          buf=atof(pch);
          if(printon==1)printf("Float value of b1 %f\n",buf);
          b1=buf;
          break;
        case 12:
          buf=atof(pch);
          if(printon==1)printf("Float value of b2 %f\n",buf);
          b2=buf;
          break;
        case 13:
          buf=atof(pch);
          if(printon==1)printf("Float value of b3 %f\n",buf);
          b3=buf;
          break;
        case 14:
          buf=atof(pch);
          if(printon==1)printf("Float value of b4 %f\n",buf);
          b4=buf;
          break;
        case 15:
          buf=atof(pch);
          if(printon==1)printf("Float value of b5 %f\n",buf);
          b5=buf;
          break;
        case 16:
          buf=atof(pch);
          if(printon==1)printf("Float value of b6 %f\n",buf);
          b6=buf;
          break;
        case 17:
          buf=atof(pch);
          if(printon==1)printf("Float value of b7 %f\n",buf);
          b7=buf;
          break;
        case 18:
          buf=atof(pch);
          if(printon==1)printf("Float value of b8 %f\n",buf);
          b8=buf;
          break;

        default:
          break;
        }
      //printf("%s in Aufruf %d\n",pch,num);
      pch=strtok(NULL," []");
      num++;
    }


}


messpunkt::~messpunkt(){}
void messpunkt::anzeigen(){

  //std::cout <<transx<<" : " <<transy<<" : "<<transz<<"\n";
  //std::cout <<rotx<<" : " <<roty<<" : "<<rotz<<"\n";
  qDebug() <<sx<<" : " <<sy<<" : "<<sz<<" : "<<b0<< " : "<<b1<<" : "<<b3<<" : "<<b4<<" : " <<b5<<" : " <<b6<<" : "<<b7<<" : " <<b8<<"\n";

}
