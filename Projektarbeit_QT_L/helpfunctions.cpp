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

void csv_einlesen(const char* path,float **matrix)
{
  QFile CSVFile(path);
  if(CSVFile.open(QIODevice::ReadWrite)){
      QTextStream Stream(&CSVFile);
      int RowNumber =0;
      while(Stream.atEnd()== false){
          QString LineData= Stream.readLine();
          QStringList Data= LineData.split(",");
          RowNumber=RowNumber+1;
          for(int i=1;i<Data.length();i++){
              if(RowNumber !=1){
                matrix[RowNumber-2][i-1]=Data.at(i).toFloat();
                //qDebug()<<"Row"<<RowNumber<<" : Column "<<i<< "Data is : " << Data.at(i).toFloat();
                }
            }
        }
    }
  CSVFile.close();
}
