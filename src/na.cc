#include<gsl/gsl_sort_double.h>
#include"model.h"
#include<math.h>
#include"useful.h"
#include"random.h"
#include<iostream>
using namespace std;
/*
    compute L2-norm misfit function 
*/
void misfit(ObsData *obs,double *loss)
{
    int i,j;
    double s = 0.0;
    for(i=0;i<obs->np;i++){
        s = 0.0;
        for(j=0;j<obs->n;j++){
            s += pow(obs->d[i][j] - obs->d0[j],2.0);
        }
        loss[i] = s/(obs->np);
    }
}

/*
    sort model according to loss, and select ns model with minimum misfit
*/
void sort_and_select(Origins *org,ObsData *obs){
    double loss[obs->np];
    int i,j;
    size_t p[org->ns];

    // compute index of the ns model with smallest loss
    org->synthetic(obs);
    misfit(obs,loss);
    gsl_sort_smallest_index(p,org->ns,loss,1,obs->np);

    // cover the first ns model
    float **m = fmat(org->ns,org->nd);
    for(i=0;i<org->ns;i++){
        fcopyvec(org->m[p[i]],m[i],org->nd);
    }

    for(i=0;i<org->ns;i++){
        fcopyvec(m[i],org->m[i],org->nd);
    }

    free_fmat(m,org->ns);

    for(i=0;i<org->ns;i++){
        cout<<i+1<<"-th model: ";
        for(j=0;j<org->nd;j++){
            cout<< org->m[i][j] << " ";
        } 
        cout << loss[p[i]] <<endl; 
    }
}

/*
    Compute Cartesian distance to i-th axis originated from point m
*/
void dist2axis_i(Origins *org,float *dist,float *m,int i)
{
    int j,k;
    for(j=0;j<org->np;j++){
        dist[j] = 0.0;
        for(k=0;k<org->nd;k++){
            if(k!=i) dist[j] += pow(org->m[j][k] - m[k],2);
        }
    }
}

/*
    use the ns model in Org as the center points of Voronoi cells,
    generate a set of new model by using random_walk in the k-th cell.
    The number of new models is np/ns 
*/
void generate_model_kth_cell(Origins *org,float **m,int num,int k)
{
    // first copy the k-th model to m0
    float m0[org->nd];
    float dist[org->np];
    fcopyvec(org->m[k],m0,org->nd);

    // then compute the distance to i-th axis originated from m0 for every model
    int i = 0;
    dist2axis_i(org,dist,m0,i);

    // do random walk
    int iter = 0;
    while(iter < num ){
        // first compute all the intersection points between i-th axis 
        // and the boundary lines for k-th and other VCs
        float x[org->np];
        for(int j = 0; j < org->np; j++){
            if(org->m[k][i] == org->m[j][i]){ 
                x[j] = org->m[k][i];
            }
            else{
                x[j] = 0.5 * (org->m[k][i]+org->m[j][i] + \
                        (dist[k]-dist[j]) / (org->m[k][i]-org->m[j][i]));
            }
        }

        // find the boundary of random walk
        float low,high;
        low = org->bound[i][0];
        high = org->bound[i][1];
        for(int j=0;j<org->np;j++){
            if(x[j]< m0[i] && x[j]>low)
                low = x[j];
            if(x[j] > m0[i] && x[j] < high)
                high = x[j];
        }
        fcopyvec(m0,m[iter],org->nd);
        m[iter][i] = rand3_bound(low,high);
        m0[i] = m[iter][i];

        // renew dist
        int next = (i+1) % org->nd;
        for(int j = 0; j <org->np;j++){
            dist[j] += pow(org->m[j][i]-m0[i],2) \
                    - pow(org->m[j][next]-m0[next],2);
        }

        // update iter
        iter += 1;
        i = next;
    }


}

void generate_model(Origins *org)
{
    int k;
    float **mnew = fmat(org->np,org->nd);

    //#pragma omp parallel for
    for(k=0;k<org->ns;k++){
        int num = org->np / org->ns;
        float **m = fmat(num,org->nd);
        generate_model_kth_cell(org,m,num,k);
        int i,j;

        for(i=0;i<num;i++){
            for(j=0;j<org->nd;j++){
                mnew[k*num+i][j] = m[i][j];
            }
        }
        free_fmat(m,num);
    }

    fcopymat(mnew,org->m,org->np,org->nd);

    free_fmat(mnew,org->np);
}

void inversion(Origins *org,ObsData *obs)
{   
    int i; 
    char line[128];
    FILE *fp;
    for(i=0;i<10000;i++){
        cout << i+1 <<"-th iteration:"<<endl;
        sort_and_select(org,obs);
        generate_model(org);
        sprintf(line,"out_model/%d.dat",i+1);
        fp = fopen(line,"w");

        for(int j=0;j<org->np;j++){
            for(int k=0;k<org->nd;k++){
                fprintf(fp,"%f ",org->m[j][k]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);

    }
}