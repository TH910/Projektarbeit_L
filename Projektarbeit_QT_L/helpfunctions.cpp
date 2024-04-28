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
          mpl.push_back(messpunkt(x,y,z));
          }
        }
    }
  CSVFile.close();
  return mpl;
}


void udp_server(){
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if ( bind(sockfd, (const struct sockaddr *)&servaddr,
          sizeof(servaddr)) < 0 )
  {
      perror("bind failed");
      exit(EXIT_FAILURE);
  }

  socklen_t len;
  int n;
  float mp[12]={0};
  len = sizeof(cliaddr);  //len is value/result
  while(1){
  n = recvfrom(sockfd, (char *)buffer, MAXLINE,
              MSG_WAITALL, ( struct sockaddr *) &cliaddr,
              &len);
  buffer[n] = '\0';
  extract_values2(mp,buffer);
  //qDebug()<<buffer;
  //printf("%s\n", buffer);
   }

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
  int printon=1;
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



