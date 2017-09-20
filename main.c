/*
 * TODO: 
 * - Parser dos comandos da linha de comando
 *    - Salvar matriz no arquivo
 *    - Ler matriz da stdin
 *    - Imprimir resultado na stdout
 * - Validar se a matriz é inversivel 
 * - Implementar refinamento
 * - Implementar a medição de tempo
 * - Implementar a geração de matrizes aleatórias
 * - Implementar os comentários dyoxigen
 * FIXME:
 * - ✓ [DONE] Função LU_decomposition: Esqueci de implementar o pivotamento do vetor b onde (Ax = b)
 * - melhorar backward and forward substitution
 * - 
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "matrix.h"

double *mallocAndCheck();
void forwardSubstitutionIdentity();
void backwardSubstitution();
void LU_Decomposition();
void swap();
void print_matrix();
double *verifyIdentity();



int main(int argc, char *argv[]){

    srand( 20172 );
    
    int c;
    int iterations; //iterative refinement

    int n;
    double *matrix;

    while ((c = getopt(argc, argv, "i:o:r:")) != -1){
      switch(c){
        case 'i':                   
          if( atoi(optarg) )  
            iterations = atoi(optarg);          
          else{
            printf("set file %s\n", optarg);
          }
          
          break;
        case 'o': printf("set output file");break;
        case 'r': 
          n = atoi(optarg);
          if( !(n > 1) || !(n < 32768) ) {
              fprintf(stderr, "option [-r N] must be a valid number (1 < N < 32768) \n");
              exit(1);
          }          
        break;

      }
    }
    
    if(!iterations){
      fprintf(stderr, "The refinement iterations -i option must be provided\n");
      exit(1);
    }

    /*Seção para testes do programa*/

    double *U = generateSquareRandomMatrix(n);
    double *T = mallocAndCheck(n);
    //copy matrix U to Test
    for(int i=0; i < n * n; ++i)
      T[i] = U[i];


    double *I  = identityMatrix(n);
    double *L = mallocAndCheck(n);
    double *Z = mallocAndCheck(n);
    double *inv = mallocAndCheck(n);

    LU_Decomposition(U, L, I, n);
    forwardSubstitutionIdentity(L, Z, I, n);
    backwardSubstitution(U, Z, inv, n); 

    double *res = verifyIdentity(T, inv , n);

 
  return 0;
}


/*==========================================================================================
 * verifyIdentity
 * Given a two matrices, returns the multiplication of the two.
 *======================================================================================== */
double * verifyIdentity(double *a, double *b, int n){

    double *out = malloc(sizeof(double) * n * n);
    double *ptrA;
    double *ptrB;
    double *ptrOut = out;

    
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
       
      ptrA = &a[i * n];
      ptrB = &b[j];
      *ptrOut = 0;

      for(int k = 0; k < n; k++){
           
           *ptrOut += *ptrA * *ptrB;
           ptrA++;
           ptrB += n;
      }
      ptrOut++;
    }
  } 
  printf("Matriz A: \n");
  print_matrix(a, n);
  printf("Matriz B: \n");
  print_matrix(b, n);

  printf("Resultado \n");
  print_matrix(out, n);

  return (out);

}

void backwardSubstitution(double *U, double *Z, double *inv, int n){
  
  for(int k=0; k < n; k++){
    
    inv[(n-1) * n + k] = Z[(n-1) * n + k] / U[n * n - 1];

    for(int i=n-2; i >= 0; i--){
      inv[i*n + k] = Z[i*n + k];
      
      for(int j = (n-1); j > i; --j)
        inv[i*n + k] -= U[i*n + j] * inv[j*n + k];
      
      inv[i*n + k] /= U[i*n + i];
    }          
  }  
}

void forwardSubstitutionIdentity(double *L, double *Z, double *I, int n){  
  //Laço mais externo itera sob cada coluna da matriz identidade
  for (int k = 0; k < n; ++k){
    Z[k] = I[k] / L[0];    

    for ( int i = 1; i < n; ++i ){  
       Z[i*n + k] = I[i*n+ k];

      for( int j = 0; j < i; ++j)
         Z[i*n + k] -= L[i*n + j] * Z[j* n + k];

       Z[i * n + k] /= L[i*n + i];
    }
  }  
}


void LU_Decomposition(double *U, double *L, double *I, int n){

  double m;
  int imax;

  //fill up the main diagonal of L matrix  with 1.0
  for ( int i = 0 ; i < n ; i++) 
    L[i*n+i] = 1.0;

  for ( int j = 0; j < n-1; ++j){

    imax = j;
    //checking pivoting criteria
    for( int i = j+1; i < n ; ++i)
      if( fabs(U[i*n + j]) > fabs(U[imax*n + j]))
        imax = i;

    if(imax != j){
      swap(U, I, imax, j, n);        
    }


    //NAÏVE GAUSS Elimination
    for ( int i = j+1; i < n; ++i){
      m = U[i*n + j] / U[j*n + j];
      L[i*n + j] = m;
      U[i*n + j] = 0.0;

      for(int k = j+1; k < n; ++k)
        U[i*n + k] -= m * U[j*n + k];
    } 
  }  

  
 // print_matrix(U, n);
 // print_matrix(L, n);

}
void swap(double* A, double * I, int imax, int j, int n){

  double aux;
  for(int i = 0; i < n; i++){
    aux = A[imax * n + i];
    A[imax * n + i] = A[j * n + i];
    A[j * n + i] = aux;

    /*
      pivoting the Identity matrix to follow the pivoting in A

    */
    aux = I[imax * n + i];
    I[imax * n + i] = I[j * n + i];
    I[j * n + i] = aux;


  }

}

