#include<stdio.h>
#include<stdlib.h>
#include <string.h>




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


void extract_values(float *mp){
    char stream[]="fr 3823\nts 44597.741924\n6dcal 1\n6df2 1 1 [0 -1.000 8 3][0.000 0.000 0.000][0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000][0 0.00 0.00 0.00]\n6d 1 [0 1.000][84.203 37.681 172.102 99.1970 6.7130 9.6575][0.979069 0.086946 0.184021 -0.166608 -0.176923 0.970021 0.116897 -0.980377 -0.158734]\n3d 0\n6dmt2 1 1 [0 -1.000 1 0.000][1.777 2.777 3.777][0.888888 1.888888 2.888888 3.888888 4.888888 5.888888 6.888888 7.888888 8.888888][0][0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00]\n6dmtr 0 0\ngl 0 \nglcal 0 \0";
    char extract_stream[250];
    char start[]= "6dmt2";
    char end[]= "6dmtr";
    char value[]="1.777";

    char *ptrStart=strstr(stream,start);
    char *ptrEnd=strstr(stream,end);
    *ptrEnd='\0';
    strcpy(extract_stream,ptrStart);
    //printf("%s",extract_stream);
    char *pch;
    pch=strtok(extract_stream," []");
    int  num=0;
    int printon=0;

    while(pch!=NULL){

        switch(num) {
            case 7:
                if(printon==1)printf("Float value of sy %f\n", strtof(pch,NULL));
                //mp[0]=strtof(pch,NULL);
                break;
            case 8:
                if(printon==1)printf("Float value of sy %f\n",strtof(pch,NULL));
                //mp[1]=strtof(pch,NULL);
                break;
            case 9:
                if(printon==1)printf("Float value of sz %f\n",strtof(pch,NULL));
                //mp[2]=strtof(pch,NULL);
                break;
            case 10:
                if(printon==1)printf("Float value of b0 %f\n",strtof(pch,NULL));
                //mp[3]=strtof(pch,NULL);
                break;
            case 11:
                if(printon==1)printf("Float value of b1 %f\n",strtof(pch,NULL));
                //mp[4]=strtof(pch,NULL);
                break;
            case 12:
                if(printon==1)printf("Float value of b2 %f\n",strtof(pch,NULL));
                //mp[5]=strtof(pch,NULL);
                break;
            case 13:
                if(printon==1)printf("Float value of b3 %f\n",strtof(pch,NULL));
                //mp[6]=strtof(pch,NULL);
                break;
            case 14:
                if(printon==1)printf("Float value of b4 %f\n",strtof(pch,NULL));
                //mp[7]=strtof(pch,NULL);
                break;
            case 15:
                if(printon==1)printf("Float value of b5 %f\n",strtof(pch,NULL));
                //mp[8]=strtof(pch,NULL);
                break;
            case 16:
                if(printon==1)printf("Float value of b6 %f\n",strtof(pch,NULL));
                //mp[9]=strtof(pch,NULL);
                break;
            case 17:
                if(printon==1)printf("Float value of b7 %f\n",strtof(pch,NULL));
                //mp[10]=strtof(pch,NULL);
                break;
            case 18:
                if(printon==1)printf("Float value of b8 %f\n",strtof(pch,NULL));
                //mp[11]=strtof(pch,NULL);
                break;

            default:
                break;
        }
        //printf("%s in Aufruf %d\n",pch,num);
        pch=strtok(NULL," []");
        num++;
    }
}
