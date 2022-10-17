#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// funções utilitários
void PrintVector(int *Vet, int N) {
  for (int x = 0; x < N; x++) {
    printf("%d |", Vet[x]);
  }
}
int *FillVector(int N, int *Vet) {
  srand(time(NULL));
  for (int x = 0; x < N; x++) {
    Vet[x] = rand() % 10;
    printf("%d |", Vet[x]);
  }
  return Vet;
}

int *newVector(int *Vet, int *Aux, int N) {
  for (int i = 0; i < N; i++) {
    Aux[i] = Vet[i];
  }
  return Aux;
}
void printTime(char* msg,int t){
    printf("Runtime %s: %lf s \n", msg, ((double)t)/((CLOCKS_PER_SEC)));
}
// InsertionSort
void InsertionSort(int N, int *Vet) {
  int i = 0;
  int key;
  for (int j = 1; j < N; j++) {
    key = Vet[j];
    i = j - 1;
    while ((Vet[i] > key) && (i >= 0)) {
      Vet[i + 1] = Vet[i];
      i = i - 1;
    }
    Vet[i + 1] = key;
  }
}
// HeapSort
void HeapDown(int i, int N, int *Vet) {
  int f = 2 * i;
  int aux;
  if (f <= N) {
    if (f < N) {
      if (Vet[f + 1] > Vet[f]) {
        f += 1;
      }
    }
    if (Vet[i] < Vet[f]) {
      int aux = Vet[i];
      Vet[i] = Vet[f];
      Vet[f] = aux;
      HeapDown(f, N, Vet);
    }
  }
}
void BuildHeap(int *Vet, int N) {
  for (int i = N / 2; i > 0; i--) {
    HeapDown(i, N, Vet);
  }
}
void HeapSort(int *Vet, int n) {
  int aux;
  BuildHeap(Vet, n);
  for (int i = n; i > 1; i--) {
    aux = Vet[0];
    Vet[0] = Vet[i];
    Vet[i] = aux;
    HeapDown(0, 1, Vet);
  }
}

void ExecuteInsertion(int *Vet, int n) {
  clock_t t;
  t = clock();
  InsertionSort(n, Vet);
  t = clock() - t;
  PrintVector(Vet, n);
  printTime("InsertionSort", t);

    
}

void ExecuteHeap(int *Vet, int n) {
  clock_t t;
  t = clock();
  HeapSort(Vet, n);
  t = clock() - t;
  PrintVector(Vet, n);
  printTime("HeapSort", t);
}
void executeHeapAndInsertion(int n) {
  int *Vet = FillVector(n, Vet);
  int *Aux = newVector(Vet, Aux, n);
  ExecuteInsertion(Vet, n);
  ExecuteHeap(Aux, n);
}
int main() {

 srand(time(NULL));

	int tam=6;
	int sizes[]={1000,10000,50000,100000,500000,1000000};
    int numExe=1;

    for(int i=0;i<tam;i++){
        printf("Entrada %d:\n", sizes[i]);
        for(int j=0; j<numExe;j++){
            executeHeapAndInsertion(sizes[i]);
        }
        puts("======================================");
    }
  return 0;
}