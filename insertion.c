#include <stdio.h>
#include <malloc.h>
#include <time.h>

int N = 10;
int M = 200000;

void insertionSort(int *v, int n) {
  int i, j, tmp;
  for (i=1; i<n; i++) {
    tmp = v[i];
    for (j=i-1; j>=0 && tmp<v[j]; j--)
      v[j+1] = v[j]; // joga para cima todos os elementos
    v[j+1] = tmp;
  }
}

void copia_vetor(int *v, int *u, int n) {
  int i;
  for (i=0; i<n; i++)
    u[i] = v[i];
}

int main(void) {
  int **v, i, j, k, *n;
  clock_t start, stop;
  double duration;
  v = malloc(N*M*sizeof(int *));
  n = malloc(N*M*sizeof(int));
/* Leitura */
  for (i=0; i<N; i++) { 
    scanf("%d", &n[i]);
    v[i] = malloc(n[i]*sizeof(int));
    for (j=0; j<n[i]; j++)
      scanf("%d", &v[i][j]);
  }
/* Alocação dos vetores restantes*/
  for (i=1; i<M; i++)
    for (j=0; j<N; j++)
      v[i*N+j] = malloc(n[j]*sizeof(int));
/* Cópia */
  for (i=0; i<M-1; i++)
    for (j=0; j<N; j++) 
      copia_vetor(v[N*i+j], v[N*(i+1)+j], n[j]);
  start = clock();
/* Algoritimo */
  for (i=0; i<N*M; i++)
    insertionSort(v[i], n[i]);
  stop = clock();
  duration = (double)(stop - start)/(double)CLOCKS_PER_SEC;
/* Impressão */
//  for (i=0; i<M; i++)
//    for (j=0; j<N; j++) {
//      for (k=0; k<n[j]; k++)
//        printf("%d ", v[j][k]);
//      printf("\n");
//    }
  printf("%e\n", duration/M);
  for (i=0; i<N*M; i++)
    free(v[i]);
  free(v);
  return 0;
}
