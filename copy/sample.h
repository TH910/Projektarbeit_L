#ifndef SAMPLE_H
#define SAMPLE_H
#include"messpunkt.h"


class sample
{
public:
  std::vector <messpunkt> daten;
  int anzahl_mp;
  double xmax;
  double xmin;
  double ymax;
  double ymin;
  double zmax;
  double zmin;
  double xmittel;
  double ymittel;
  double zmittel;
  //Konstruktor
  sample(std::vector <messpunkt> daten);
  //Destruktor
  ~sample();
};

#endif // SAMPLE_H
