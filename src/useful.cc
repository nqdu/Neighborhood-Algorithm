#include<iostream>
#include<math.h>
#include"useful.h"
using namespace std;

int *ivec(int n){
    int *a=new int[n];
    return a;
}

float *fvec(int n){
    float *a=new float[n];

    return a;
}

double *dvec(int n){
    double *a=new double[n];

    return a;
}

int **imat(int m,int n){
    int **a;
    int i;

    a=new int*[m];
    for(i=0;i<m;i++)
        a[i]=new int[n];
    
    return a;
}

float **fmat(int m,int n){
    float **a;
    int i;

    a=new float*[m];
    for(i=0;i<m;i++)
        a[i]=new float[n];
    
    return a;
}

double **dmat(int m ,int n){
    double **a;
    int i;
    a=new double*[m];

    for(i=0;i<m;i++)
        a[i]=new double[n];
    
    return a;
}

int ***i3tensor(int m,int n,int t){
    int ***a;
    int i;
    a=new int**[m];

    for(i=0;i<m;i++)
        a[i]=imat(n,t);
    
    return a;
}

float ***f3tensor(int m ,int n,int t){
    float ***a;
    int i;
    a=new float**[m];

    for(i=0;i<m;i++)
        a[i]=fmat(n,t);
    
    return a;    
}

double ***d3tensor(int m ,int n,int t){
    double ***a;
    int i;
    a=new double**[m];

    for(i=0;i<m;i++)
        a[i]=dmat(n,t);
    
    return a;    
}

void free_ivec(int *a){
    delete [] a;
    a=NULL;
}

void free_fvec(float *a){
    delete [] a;
    a=NULL;
}

void free_dvec(double *a){
    delete [] a;
    a=NULL;
}

void free_imat(int **a,int m){
    int i;
    for(i=0;i<m;i++)
        free_ivec(a[i]);
    delete []a;
    a=NULL;
}

void free_fmat(float **a,int m){
    int i;
    for(i=0;i<m;i++)
        free_fvec(a[i]);
    delete []a;
    a=NULL;
}

void free_dmat(double **a,int m){
    int i;
    for(i=0;i<m;i++)
        free_dvec(a[i]);
    delete []a;
    a=NULL;
}

void free_i3tensor(int ***a,int m,int n){
    int i;
    for(i=0;i<m;i++)
        free_imat(a[i],n);
    delete []a;
    a=NULL;
}

void free_f3tensor(float ***a,int m,int n){
    int i;
    for(i=0;i<m;i++)
        free_fmat(a[i],n);
    delete []a;
    a=NULL;   
}

void free_d3tensor(double ***a,int m,int n){
    int i;
    for(i=0;i<m;i++)
        free_dmat(a[i],n);
    delete []a;
    a=NULL;   
}

void fcopymat(float **a,float **b,int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            b[i][j]=a[i][j];
}

void dcopymat(double **a,double **b,int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            b[i][j]=a[i][j];
}

void fcopyvec(float *a,float *b,int n)
{
    int i;
    for( i=0;i<n;i++)
        b[i] = a[i];
}