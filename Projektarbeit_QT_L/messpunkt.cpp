#include "messpunkt.h"

messpunkt::messpunkt(float tx,float ty,float tz,float r0,float r1,float r2,float r3,float r4,float r5,float r6,float r7,float r8)
  :sx(tx),sy(ty),sz(tz),b0(r0),b1(r1),b2(r2),b3(r3),b4(r4),b5(r5),b6(r6),b7(r7),b8(r8){}

messpunkt::messpunkt(float tx,float ty, float tz): sx(tx), sy(ty), sz(tz),b0(0),b1(0),b2(0),b3(0),b4(0),b5(0),b6(0),b7(0),b8(0){}

messpunkt::messpunkt(char *stream){

  char extract_stream[250];
  char start[]= "6dmt2";
  char end[]= "6dmtr";

  QString myvalue;
  char *ptrStart=strstr(stream,start);
  char *ptrEnd=strstr(stream,end);
  *ptrEnd='\0';
  strcpy(extract_stream,ptrStart);
  //printf("%s",extract_stream);
  char *pch;
  pch=strtok(extract_stream," []");
  int  num=0;
  int printon=0;
  float buf=0;
  while(pch!=NULL){

      switch(num) {
          case 7:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of sy %f\n", buf);
              sx=buf;
              break;
          case 8:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of sy %f\n",buf);
              sy=buf;
              break;
          case 9:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of sz %f\n",buf);
              sz=buf;
              break;
          case 10:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b0 %f\n",buf);
              b0=buf;
              break;
          case 11:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b1 %f\n",buf);
              b1=buf;
              break;
          case 12:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b2 %f\n",buf);
              b2=buf;
              break;
          case 13:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b3 %f\n",buf);
              b3=buf;
              break;
          case 14:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b4 %f\n",buf);
              b4=buf;
              break;
          case 15:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b5 %f\n",buf);
              b5=buf;
              break;
          case 16:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b6 %f\n",buf);
              b6=buf;
              break;
          case 17:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b7 %f\n",buf);
              b7=buf;
              break;
          case 18:
              myvalue=pch;
              buf=myvalue.toFloat();
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
