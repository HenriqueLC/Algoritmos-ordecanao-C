#include <stdio.h>
#include <malloc.h>
#include <time.h>

int N = 10;
int M = 200000;

void ajusta_heap (int *v, int i, int n) {
  int esq, dir, menor, aux;
/* Enquanto não é folha */
  while (i < n/2) {
    esq = i*2+1;
    dir = i*2+2;
/* Seleciona o menor dos filhos */
    if (v[esq] < v[dir] || dir >= n)
      menor = esq;
    else
      menor = dir;
/* Se o pai for maior que o menor dos filhos, troca; mas se não ocorrer troca, quebra o laço. */
    if (v[i] > v[menor]) {
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
      i = menor;
    }
    else
      return;
  }
}

void constroi_heap(int *v, int n) {
  int i;
/* Inspeciona desde o primeiro elemento que não é folha, até a raiz */
  for (i=n/2-1; i>=0; i--)
    ajusta_heap(v, i, n);
}

void inverte_vetor(int *v, int n) {
  int i, j, tmp;
  for (i=0, j=n-1; i<n/2; i++, j--) {
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
  }
}

void heapSort(int *v, int n) {
  int tmp, i;
  constroi_heap(v, n);
/* Remove o primeiro elemento, adiciona ao final do vetor (não heap), ajusta o heap e atualiza o tamanho do heap */
  for (i=n-1; i>=0; i--) {
    tmp = v[i];
    v[i] = v[0];
    v[0] = tmp;
    ajusta_heap(v, 0, i);
  }
  inverte_vetor(v, n);
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
    heapSort(v[i], n[i]);
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
