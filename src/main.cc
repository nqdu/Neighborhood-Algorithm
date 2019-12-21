#include<iostream>
#include<stdlib.h>
#include"model.h"
#include"useful.h"
#include"na.h"

int main(){
    Origins org;
    ObsData obs;
    char quakefile[128]="input/quake.in";
    char datafile[128]="input/data.in";

    init_model(&org,&obs,quakefile,datafile);

    inversion(&org,&obs);
    FILE *fp;
    fp = fopen("error.txt","w");
    for(int i=0;i<obs.np;i++){
        for(int j=0;j<obs.n;j++){
            fprintf(fp,"%f ",obs.d[i][j]-obs.d0[j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    org.free();
    obs.free();

    return 0;
}