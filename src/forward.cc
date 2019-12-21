#include<math.h>

void forward(float *x,float *y,float *model,int m,double *t)
/*
    compute traveltime for a given model, save results in t
*/
{
    int i,j;
    float x0=model[0],y0=model[1],z0=model[2];
    float t0=model[3],v=model[4];
    double s;

    for(i=0;i<m;i++){
        s=pow(x[i]-x0,2)+pow(y[i]-y0,2)+z0*z0;
        t[i]=sqrt(s)/v+t0;
    }
}
