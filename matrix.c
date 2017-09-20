#import "matrix.h"
#import <stdio.h>
#import <stdlib.h>
#import <string.h>



double *readMatrixFromFile(char* filename){

    
   
    FILE* fh;
    unsigned int n;
    double *ptr;
    float vl;
    
    
    if ((fh = fopen(filename, "r")) == NULL){
        fprintf(stderr, "Erro: Could not open %s \n", filename );
        exit(1);
    }

    if ( fscanf(fh, "%d", &n) == EOF){
        fprintf(stderr, "Error: Failed to read from file");
        exit(1);
    }
    
    int elements = n * n;
    double *data = mallocAndCheck(n);

    ptr = data;

    int i;
    for (i = 0; i < elements; ++i){            
        if (fscanf(fh, "%f", &vl) == EOF){
            fprintf(stderr, "Error: File is incomplete");
            exit(1);
        }        
        *(ptr++) = vl;
    }
    
    fclose(fh);
    return data;
}

double *generateSquareRandomMatrix( unsigned int n ){
    double *mat =  mallocAndCheck(n);
  
    /* generate a randomly initialized matrix in row-major order */
    double *ptr = mat;
    double *end = mat + n*n;
  
    double invRandMax = 1.0/(double)RAND_MAX;
  
    while( ptr != end ) {
      *ptr++ = (double)rand() * invRandMax;
    }
  
    return (mat);
  }

double* identityMatrix(int n){
    
    double *mat = mallocAndCheck(n);
    
    double *ptr = mat;
    for(int i=0; i < n; i++){
        *ptr = 1.0;
        ptr += n + 1;
    }

    return (mat);
}

double *mallocAndCheck(int n){
    
     double *mat = NULL;
 
    if ( ! (mat = (double *) malloc(n*n*sizeof(double))) ){
        fprintf(stderr, "Error: Memory allocation failed.");
        exit(1);
    }

     for(int i = 0; i < n; ++i) mat[i] = 0.0;
    
     return (mat); 
    
}

void print_matrix(double *mat, int n){
    
    double *ptr = mat;
  
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        printf("| %.15f | ", *(ptr++));
      printf("\n");
    }
  
    return;
  }
  
  