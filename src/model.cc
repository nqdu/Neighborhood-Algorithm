#include<stdlib.h>
#include<iostream>
#include"model.h"
#include"useful.h"
#include"forward.h"
using namespace std;

int Origins :: init(char *filename)
{
    FILE *fp;
    char line[256];
    fp = fopen(filename, "r");

    // read np,ns,nd
    fgets(line, sizeof(line), fp);
    sscanf(line,"%d%d%d",&np,&ns,&nd);
    bound = fmat(nd,2);
    m0 = fvec(nd);
    m = fmat(np,nd);

    // read boundaries
    int i,j;
    for(i=0;i<nd;i++){
        fgets(line, sizeof(line), fp);
        sscanf(line,"%f%f",bound[i],bound[i]+1);
    }

    // read synflag
    fgets(line, sizeof(line), fp);
    sscanf(line,"%d",&synflag);
    if(synflag ==1){
        for(i=0;i<nd;i++){
            fgets(line, sizeof(line), fp);
            sscanf(line,"%f",m0+i);
        }
        fgets(line, sizeof(line), fp);
        sscanf(line,"%f",&noise);
    }
    // read 


    // generate new model
    for(i=0;i<np;i++){
        for(j=0;j<nd;j++){
            m[i][j] = (float)rand3_bound(bound[j][0],bound[j][1]);
        }
    }
    
    fclose(fp);
    return 1;
}

int Origins :: free(){
    free_fmat(bound,nd);
    free_fmat(m,np);
    free_fvec(m0);

    return 1;
}

int Origins ::synthetic(ObsData *obs)
{
    int i,j;
    for(i=0;i<np;i++){
        forward(obs->x,obs->y,m[i],nd,obs->d[i]);
    }

    return 1;
}

int ObsData :: init(char *filename){
    FILE *fp;
    fp = fopen(filename,"r");

    fscanf(fp,"%d",&n);
    x = fvec(n);
    y = fvec(n);
    d0 = dvec(n);

    int i;
    for(i=0;i<n;i++){
        fscanf(fp,"%f%f",x+i,y+i);
    }

    return 1;
}

int ObsData :: free(){
    free_dvec(d0);
    free_dmat(d,np);
    free_fvec(x);
    free_fvec(y);

    return 1;
}

// read quake model,datamodel and do some preprocessing work
int init_model(Origins *org,ObsData *obs,char *quakefile,char *datafile)
{
    org->init(quakefile);
    obs->init(datafile);
    obs->d = dmat(org->np,obs->n);

    obs->np = org->np;
    if(org->synflag ==1){
        forward(obs->x,obs->y,org->m0,obs->n,obs->d0);
        int i; 
        for(i=0;i<obs->n;i++){
            obs->d0[i] *= 1.0+ gaussian()*org->noise;
        }
    }

    return 1;
}