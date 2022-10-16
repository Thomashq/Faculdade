#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// funções utilitários
void VectorToVector(int *Vet, int *Aux, int N) {
  for (int i = 0; i < N; i++) {
    Aux[i] = Vet[i];
  }
}
void PrintVetor(int *Vet, int N){
    for (int x = 0; x < N; x++) {
    printf("%d |", Vet[x]);
    }
  }
void FillVector(int N, int *Vet) {
  srand(time(NULL));
  for (int x = 0; x < N; x++) {
    Vet[x] = rand() % 10;
    printf("%d |", Vet[x]);
  }
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
  if(f <= N) {
    if(f < N){
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
void BuildHeap(int *Vet, int N){
  for(int i = N/2 ; i > 0 ; i--){
    HeapDown(i, N, Vet);    
  }
}
void HeapSort(int *Vet, int n) {
  int aux;
  BuildHeap(Vet, n);
  for(int i = n ; i > 1 ; i--){
    aux = Vet[0];
    Vet[0] = Vet[i];
    Vet[i] = aux;
    HeapDown(0 , 1, Vet);
  }
}
int main(void) {

  int n = 10, i;
  int Vet[n];
  int Aux[n];
  int key = 0;

  // insertionSort
  puts("InsertionSort: ");
  FillVector(n, Vet);
  puts("");
  InsertionSort(n, Vet);
  PrintVetor(Vet, n); 
  puts("");

  // heapSort
  puts("HeapSort: ");
  FillVector(n, Vet);
  HeapSort(Vet, n);
  puts("");
  PrintVetor(Vet, n);
  puts("");
  return 0;
}