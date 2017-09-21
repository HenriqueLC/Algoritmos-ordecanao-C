#include <stdio.h>
#include <malloc.h>
#include <time.h>

int N = 10;
int M = 200000;

void troca(int *v, int i, int j) {
  int aux;
  aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

void quickSort(int *v, int inicio, int fim) {
  int i, j, pivo;
  i = inicio;
  j = fim;
  pivo = (v[inicio]+v[fim])/2;
  while (i < j) {
  /* Atualiza os indices i e j de tal forma que eles referenciem os valores a serem mutuamente trocados */ 
    while (v[i] < pivo)
      i++;
    while (v[j] > pivo)
      j--;
  /* Se i <= j, ou seja, se i e j não ultrapassaram a posição de referência do pivô, realiza a troca e atualiza os índices */
    if (i <= j) {
      troca(v, i, j);
      i++;
      j--;
    }
  }
  /* Uma vez que j e i referenciam os elementos imediatamente antes e depois do pivô, respectivamente, realiza novo particionamento */
  if (j > inicio)
    quickSort(v, inicio, j);
  if (i < fim)
    quickSort(v, i, fim);
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
    quickSort(v[i], 0, n[i]);
  stop = clock();
  duration = (double)(stop - start)/(double)CLOCKS_PER_SEC;
/* Impressão */
//  for (i=0; i<N; i++) {
//    for (j=0; j<n[i]; j++)
//      printf("%d ", v[i][j]);
//    printf("\n");
//   }
  printf("%e\n", duration/M);
  for (i=0; i<N*M; i++)
    free(v[i]);
  free(v);
  return 0;
}
