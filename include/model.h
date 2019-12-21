#pragma once 
#include"random.h"
class ObsData{
public:
    int n;  // length of data vector
    int np; // number of models;
    float *x,*y; // receiver coordinates, shape(n,)
    double *d0; // true data
    double **d; // data matrix for every model, shape(np,n)

    // functions
    int init(char *filename); 
    int free();
};

class Origins{
    public:
    int np,ns,nd;     // number of models, no. of selected models, and model dimension
    int synflag;    // whether or not to synthetic data
    float noise;    // noiselevel
    float **bound;  // domain of model, shape(nd,2)
    float *m0;      // true model;
    float **m;      // model matrix, shape(np,nd)

    // functions
    int init(char *filename);
    int synthetic(ObsData *obs);
    int free();
};

int init_model(Origins *org,ObsData *obs,char *quakefile,char *datafile);