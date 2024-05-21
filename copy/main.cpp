#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QLocale>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include <signal.h>
#include <semaphore.h>
#include <chrono>
#include "messpunkt.h"
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "sample.h"
#include <QLCDNumber>
#include "printer.h"
#include "helpfunctions.h"

#define PORT     5000
#define MAXLINE 1024

sem_t mutex;
sem_t empty;
sem_t full;


void wf(std::vector<messpunkt> &vec, unsigned int size,printer &p,double toleranz, int &flag){
  int sockfd;

  char buffer[MAXLINE];

  struct sockaddr_in servaddr, cliaddr;
  char ip[]="192.168.188.41";
  //char ip[]="192.168.0.137";
  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
    }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = inet_addr(ip);
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
  len = sizeof(cliaddr);  //len is value/result
  std::vector<messpunkt> vecbuf;
  messpunkt actual_mp, last_mp;

  double a=1;
  while(1){
      n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                   MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                   &len);
      buffer[n] = '\0';
      actual_mp=messpunkt(buffer);

      if(((actual_mp.sx-last_mp.sx)<=toleranz) &&((actual_mp.sy-last_mp.sy)<=toleranz)&&((actual_mp.sz-last_mp.sz)<=toleranz)){
          p.set_state(1);
        }else {
          p.set_state(0);
        }
      p.print_values(actual_mp.sx,actual_mp.sy,actual_mp.sz);


      if(flag==0){
          vecbuf.push_back(actual_mp);
          if(size==vecbuf.size()){
              sem_wait(&empty);
              sem_wait(&mutex);

              vec=vecbuf;

              sem_post(&mutex);
              sem_post(&full);

              vecbuf.clear();
            }
        }

      last_mp=actual_mp;
    }
}




void rf(std::vector<messpunkt> &vec,std::vector<messpunkt> &vecmittel,int size,double toleranz, unsigned int anzahl_punkte, int &flag,printer &p){
  std::vector<messpunkt> vecbuf2;

  //float xmax,xmin,ymax,ymin,zmax,zmin;
  while(1){
      //z++;
      sem_wait(&full);
      sem_wait(&mutex);

      vecbuf2=vec;
      vec.clear();
      //std::cout<<"Copy von Vector2 mit size"<<vecbuf2.size()<< std::endl;
      sem_post(&mutex);
      sem_post(&empty);

      if(vecbuf2.size()!=0){
          sample test=sample(vecbuf2);

          if((test.xmax-test.xmin<= toleranz)&&(test.ymax-test.ymin<= toleranz) &&(test.zmax-test.zmin<= toleranz)){
              vecmittel.push_back(messpunkt(test.xmittel,test.ymittel,test.zmittel));
              p.receive_data(vecmittel.size());
              std::cout<< "###########"<< std::endl;
              std::cout<<" Wert gespeichert"<<"  Größe des Vector: "<< vecmittel.size()<<std::endl;
              std::cout<<"X: "<<test.xmittel<<" Y: "<<test.ymittel<< " Z: "<< test.zmittel<< std::endl;
              std::cout<< "###########"<< std::endl;
            }

          if(vecmittel.size()==anzahl_punkte){
              std::cout<<"Alle Werte wurden abgespeichert"<<std::endl;
              flag=1;
              break;

            }

        }
    }
  std::cout<<"Read Schleife beendet"<<std::endl;
  std::cout<<"Die abgespeicherten Mittelwerte lauten"<<std::endl;
  for (auto ele: vecmittel){
      ele.anzeigen();
    }
}


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  printer p;
  QObject::connect(&p, &printer::receive_signal,&w, &MainWindow::receive_slot);
  QObject::connect(&p, &printer::print_signal,&w, &MainWindow::print_slot);
  QObject::connect(&p, &printer::state_signal,&w, &MainWindow::state_slot);
  std::setlocale(LC_ALL,"en_US.UTF-8");
  w.show();
  std::vector<messpunkt> vec;
  std::vector<messpunkt> vecmittel;
  int size=120;
  double toleranz=2.5;
  unsigned int anzahl_punkte=6;
  int flag=0;
//Test
  std::vector<messpunkt> test;
  for(int k=0;k<6;k++){
     test.push_back(messpunkt(k,k,k));
    }

  double testarr[3][3];




  std::thread t1(wf, std::ref(vec),size,std::ref(p),toleranz,std::ref(flag));
  std::thread t2(rf, std::ref(vec),std::ref(vecmittel),size,toleranz, anzahl_punkte,std::ref(flag),std::ref(p));
  if (sem_init(&mutex, 0, 1) == -1)
    std::cerr << "Error: semaphore" << std::endl;

  if (sem_init(&empty, 0, 1) == -1)
    std::cerr << "Error: semaphore" << std::endl;

  if (sem_init(&full, 0, 0) == -1)
    std::cerr << "Error: semaphore" << std::endl;


  while(1){
      a.processEvents();
      usleep(10000);

    }

  t1.join();
  t2.join();

  // return a.exec();
}
