#include "helpfunctions.h"
#include <vector>
#include <iostream>
#include "rapidcsv.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QtGui>


void print_array_2D(float ** output,int rows,int cols)
{
    for(int i=0; i<rows ;i++){
        for(int j=0; j< cols; j++){
            std::cout<<output[i][j]<< " ";
        }
        std::cout << std::endl;
    }
}

std::vector<messpunkt> csv_einlesen(const char* path)
{
  std::vector<messpunkt> mpl;
  QFile CSVFile(path);
  if(CSVFile.open(QIODevice::ReadWrite)){
      QTextStream Stream(&CSVFile);
      int RowNumber =0;
      float x=0,y=0,z=0;
      while(Stream.atEnd()== false){
          QString LineData= Stream.readLine();
          QStringList Data= LineData.split(",");
          RowNumber=RowNumber+1;
          for(int i=1;i<Data.length();i++){
              if(RowNumber !=1){
                  if(i==1)x=Data.at(i).toFloat();
                  if(i==2)y=Data.at(i).toFloat();
                  if(i==3)z=Data.at(i).toFloat();
                //qDebug()<<"Row"<<RowNumber<<" : Column "<<i<< "Data is : " << Data.at(i).toFloat();
                }
            }
          if(RowNumber !=1){
          mpl.push_back(messpunkt(x,y,z,0,0,0));
          }
        }
    }
  CSVFile.close();
  return mpl;
}

void extract_values2(float *mp,char *stream){
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
              mp[0]=buf;
              break;
          case 8:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of sy %f\n",buf);
              mp[1]=buf;
              break;
          case 9:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of sz %f\n",buf);
              mp[2]=buf;
              break;
          case 10:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b0 %f\n",buf);
              mp[3]=buf;
              break;
          case 11:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b1 %f\n",buf);
              mp[4]=buf;
              break;
          case 12:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b2 %f\n",buf);
              mp[5]=buf;
              break;
          case 13:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b3 %f\n",buf);
              mp[6]=buf;
              break;
          case 14:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b4 %f\n",buf);
              mp[7]=buf;
              break;
          case 15:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b5 %f\n",buf);
              mp[8]=buf;
              break;
          case 16:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b6 %f\n",buf);
              mp[9]=buf;
              break;
          case 17:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b7 %f\n",buf);
              mp[10]=buf;
              break;
          case 18:
              myvalue=pch;
              buf=myvalue.toFloat();
              if(printon==1)printf("Float value of b8 %f\n",buf);
              mp[11]=buf;
              break;

          default:
              break;
      }
      //printf("%s in Aufruf %d\n",pch,num);
      pch=strtok(NULL," []");
      num++;
  }
}

