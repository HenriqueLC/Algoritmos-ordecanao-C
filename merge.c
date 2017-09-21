#include <stdio.h>
#include <malloc.h>
#include <time.h>

int N = 10;
int M = 200000;

void intercala(int *v, int n) {
  int i, j, k, meio, *tmp;
  /* Aloca um vetor temporario de tamanho n */
  if (n > 0)
    tmp = malloc(n*sizeof(int));
  else
    return;
  
  meio = n/2;
  /* Compara e copia de forma intercalada os valores dos subvetores para o vetor temporario */
  for (i=0, j=meio, k=0; i < meio && j < n; k++)
    if (v[i] < v[j])
      tmp[k] = v[i++];
    else
      tmp[k] = v[j++];
  /* Copia os valores não especionados de um dos subvetores para o vetor temporario */
  if (i == meio)
    while (j < n)
      tmp[k++] = v[j++];
  else
    while (i < meio)
      tmp[k++] = v[i++];
  /* Copia os valores do vetor temporario para o vetor final */
  for (i=0; i<n; i++)
    v[i] = tmp[i];
  free(tmp);
}

void mergeSort(int *v, int n) {
  int meio;
  if (n > 1) {
    meio = n/2;
    mergeSort(v, meio);
    mergeSort(v+meio, n-meio);
    intercala(v, n);
  }
}

void copia_vetor(int *v, int *u, int n) {
  int i;
  for (i=0; i<n; i++)
    u[i] = v[i];
}

int main(void) {
  int **v, i, j, *n;
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
    mergeSort(v[i], n[i]);
  stop = clock();
  duration = (double)(stop - start)/(double)CLOCKS_PER_SEC;
/* Impressão */
//  for (i=0; i<N; i++) {
//    for (j=0; j<n[i]; j++)
//      printf("%d ", v[i][j]);
//    printf("\n");
//    }
  printf("%e\n", duration/M);
  for (i=0; i<N*M; i++)
    free(v[i]);
  free(v);
  return 0;
}
