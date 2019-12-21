#include<stdio.h>
#include"useful.h"
#include<gsl/gsl_rng.h>
#include<math.h>

/*
    Generate random number in (0-1)
*/
double rand3()
{   
    static int random_flag_in=0;
    static gsl_rng *gsl_r;

    double u;
    gsl_rng_env_setup();
    if(random_flag_in==0){
        gsl_r=gsl_rng_alloc(gsl_rng_taus113);
    }
    
    u=gsl_rng_uniform(gsl_r);

    random_flag_in=1;
    return u;
}

/*
    generate model in range(a,b)
*/
double rand3_bound(double a,double b){
    double x = rand3();
    x = a + (b-a) * x;

    return x;
}

/*
    Generate standard gaussian noise 
    Box-Muller algorithm is used
*/
double gaussian()
{
    double u1,u2,z;
    u1 = rand3();
    u2 = rand3();
    z =   sqrt(-2. * log(u1)) * sin(2*3.1415926535898 * u2);

    return z;
}

