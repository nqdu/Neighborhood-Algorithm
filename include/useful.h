#define pi 3.1415926535898
#define earth 6371.0

int *ivec(int n);
float *fvec(int n);
double *dvec(int n);
int **imat(int m,int n);
float **fmat(int m,int n);
double **dmat(int m ,int n);
int ***i3tensor(int m,int n,int t);
float ***f3tensor(int m ,int n,int t);
double ***d3tensor(int m ,int n,int t);

void free_ivec(int *a);
void free_fvec(float *a);
void free_dvec(double *a);
void free_imat(int **a,int n);
void free_fmat(float **a,int n);
void free_dmat(double **a,int n);
void free_i3tensor(int ***a,int m,int n);
void free_f3tensor(float ***a,int m,int n);
void free_d3tensor(double ***a,int m,int n);
void fcopymat(float **a,float **b,int m,int n);
void fcopyvec(float *a,float *b,int n);