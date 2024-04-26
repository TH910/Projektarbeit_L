#include<stdio.h>
#include<stdlib.h>

float **aufbau_matrix(int zeile, int spalte)
{
    float **matrix =malloc (zeile*sizeof(float*));
    if(NULL ==matrix){
        printf("Kein virtueller RAM mehr vorhanden");

    }
    for(int i=0;i<zeile;i++) {
        matrix[i]=malloc(spalte *sizeof(float));
        if(NULL==matrix[i]){
            printf("Kein Speicher mehr fuer Zeile %d\n",i);

        }
    }
    return matrix;
}

void abbau_matrix(float **matrix, int zeile)
{
    for(int i=0;i<zeile;i++){
        free(matrix[i]);
    }
    free(matrix);
}
