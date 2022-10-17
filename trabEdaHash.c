#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *FillVector(int tam) {
  int *Vet = (int *)malloc(tam * sizeof(int));
  if (Vet != NULL) {
    for (int i = 0; i < tam; i++) {
      int aux = (((rand() & 255) << 8 | (rand() & 255)) << 8 | (rand() & 255))
                    << 7 |
                (rand() & 127);
      Vet[i] = aux % 2000000001;
      return Vet;
    }
  }
}
int DivisionMethod(int chaveValue, int tam) { return chaveValue % tam; }

int executeDvisionHash(int *Vet, int tam, int *hashTable, int hashTam) {
  int colisions;
  for (int i = 0; i < tam; i++) {
    int aux = DivisionMethod(Vet[i], hashTam);
    if (hashTable[aux] != -1) {
      colisions++;
    }
  }
  return colisions;
}

void executeHash(int *n, int tam) {
  int tamTable = 10000;
  int *tabDivision = FillVector(tamTable);

  int colisionsDivision = executeDvisionHash(n, tam, tabDivision, tamTable);

  printf("Divisão \t N: %d\t Colisoes: %d \n", tam, colisionsDivision);
}
int main() {
  srand(time(NULL));
  int nTam[] = {200000, 400000, 600000, 800000, 1000000};

  for (int i = 0; i < 5; i++) {
    int *n = FillVector(nTam[i]);
    executeHash(n, nTam[i]);
  }
}