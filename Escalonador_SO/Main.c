/*
    Estrutura Base
 *-  Inteiro para Processos e Inteiro para Recursos
 *-  Vetor de Recursos Existentes
 *-  Vetor de Recursos Disponíveis
 *-  Matriz dos recursos já alocados para os Processos
 *-  Matriz da requisições de Recursos dos processos

 *-  Matriz Adjacente que representa o Grafo de Recursos para Processos
 *-  Função que checa o cíclo no grafo
 *-  Função que checa se é possível um Processo concluir com o recursos disponíveis.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int P, R, L;

int *All_R = NULL, *Available_R = NULL;

int **In_Use_R, **Required_R;

bool allocateResources() {
    int *Rn = (int *)malloc(R * sizeof(int));

    for (int i = 0; i < P; i++) {
        for (int u = 0; u < R; u++) {
            Rn[u] = Available_R[u];
        }

        int DoNothing = 0;
        for (int j = 0; j < R; j++) {
            DoNothing += Required_R[i][j];
        }

        int CanAllocate = 1;
        for (int j = 0; j < R; j++) {
            if (Rn[j] < Required_R[i][j]) {
                CanAllocate = 0;
            }
        }

        if (DoNothing == 0) {
            // Do Nothing
        } else if (CanAllocate) {
            for (int j = 0; j < R; j++) {
                In_Use_R[i][j] += Rn[j];
                Required_R[i][j] = 0;
                Available_R[j] = 0;
            }
            return true;
        }

        /*
        if (Required_R[i][0] == 0 && Required_R[i][1] == 0 && Required_R[i][2] == 0 && Required_R[i][3] == 0) {
            // Do Nothing
        } else if (R1 >= Required_R[i][0] && R2 >= Required_R[i][1] && R3 >= Required_R[i][2] && R4 >= Required_R[i][3]) {
            In_Use_R[i][0] += R1;
            Required_R[i][0] = 0;
            In_Use_R[i][1] += R2;
            Required_R[i][1] = 0;
            In_Use_R[i][2] += R3;
            Required_R[i][2] = 0;
            In_Use_R[i][3] += R4;
            Required_R[i][3] = 0;
            Available_R[0] -= R1;
            Available_R[1] -= R2;
            Available_R[2] -= R3;
            Available_R[3] -= R4;
            return true;
        }
        */
    }
    return false;
}

void runProcess() {
    for (int i = 0; i < P; i++) {
        int DoNothing = 0;
        for (int j = 0; j < R; j++) {
            DoNothing += In_Use_R[i][j];
        }

        int CanProcess = 0;
        for (int j = 0; j < R; j++) {
            CanProcess += Required_R[i][j];
        }

        if (DoNothing == 0) {
            // Do Nothing
        } else if (CanProcess == 0) {
            for (int j = 0; j < R; j++) {
                Available_R[j] += In_Use_R[i][j];
                In_Use_R[i][j] = 0;
            }
            printf("\n\t| PROCESS %d FINISHED  ^u^ |\n", i + 1);
        }

        /*
        if (In_Use_R[i][0] == 0 && In_Use_R[i][1] == 0 && In_Use_R[i][2] == 0 && In_Use_R[i][3] == 0) {
            // Do Nothing
        } else if (Required_R[i][0] == 0 && Required_R[i][1] == 0 && Required_R[i][2] == 0 && Required_R[i][3] == 0) {
            Available_R[0] += In_Use_R[i][0];
            Available_R[1] += In_Use_R[i][1];
            Available_R[2] += In_Use_R[i][2];
            Available_R[3] += In_Use_R[i][3];
            In_Use_R[i][0] = In_Use_R[i][1] = In_Use_R[i][2] = In_Use_R[i][3] = 0;
            printf("\n\t| PROCESS %d FINISHED ;] |\n", i + 1);
        }
        */
    }
}

void checkDeadLock() {
    int *ActiveProcess = (int *)malloc(P * sizeof(int));
    for (int i = 0; i < P; i++) {
        ActiveProcess[i] = 1;
    }

    for (int i = 0; i < P; i++) {
        int sum = 0;
        for (int j = 0; j < R; j++) {
            sum += In_Use_R[i][j] + Required_R[i][j];
        }
        if (sum == 0)
            ActiveProcess[i] = 0;
    }

    for (int i = 0; i < P; i++) {
        if (ActiveProcess[i]) {
            for (int j = 0; j < R; j++) {
                if(Required_R[i][j] != 0) {
                    int WaitingResource = Required_R[i][j] - Available_R[j];
                    if(WaitingResource > 0)
                        printf("\n\t| PROCESS %d WAITING FOR %d INSTANCES OF R%d  ^~^ |\n",i+1, WaitingResource, j+1);
                }
            }
            printf("\n");
        }
    }
}

void FillVec(int **Vector, FILE *fp, char first) {
    free(*Vector);

    int *tmp = (int *)malloc(R * sizeof(int));
    int count = 1;  // Pulamos o valor 0 por já estarmos o recebendo

    tmp[0] = atoi(&first);
    while (count < R) {
        char const ch = fgetc(fp);
        if (!isspace(ch)) {
            tmp[count] = atoi(&ch);
            count++;
        }
    }
    *Vector = tmp;
}

void FillMat(int ***Matriz, FILE *fp, char first) {
    free(*Matriz);

    int **line = (int **)malloc(P * sizeof(int *));
    int *column = NULL;
    FillVec(&column, fp, first);
    line[0] = column;

    int count = 1;
    while (count < P) {
        first = fgetc(fp);
        if (!isspace(first)) {
            column = NULL;
            FillVec(&column, fp, first);
            line[count] = column;
            count++;
        }
    }

    *Matriz = line;
}

/*  Manipula ações do arquivo, com a leitura do mesmo preenche as matrizes   */
void FileHandling(char const *File_Name, char *mode) {
    FILE *fp;
    fp = fopen(File_Name, mode);

    bool checkData[6] = {false, false, false, false, false, false};
    while (1) {
        char const ch = fgetc(fp);
        if (ch == EOF)
            break;
        if (!isspace(ch)) {
            if (!checkData[0]) {
                P = atoi(&ch);
                checkData[0] = true;
            } else if (!checkData[1]) {
                R = atoi(&ch);
                checkData[1] = true;
            } else if (!checkData[2]) {
                FillVec(&All_R, fp, ch);
                checkData[2] = true;
            } else if (!checkData[3]) {
                FillVec(&Available_R, fp, ch);
                checkData[3] = true;
            } else if (!checkData[4]) {
                FillMat(&In_Use_R, fp, ch);
                checkData[4] = true;
            } else if (!checkData[5]) {
                FillMat(&Required_R, fp, ch);
                checkData[5] = true;
            } else {
                break;
            }

            /*
            switch (data) {
                case 0:
                    P = atoi(&ch);
                    data += 1;
                    break;
                case 1:
                    R = atoi(&ch);
                    data += 1;
                    break;
                case 2:
                    FillVec(&All_R, fp, ch);
                    data += R - 1;  // A quantidade de dados da função é igual a os Recursos porém o primeiro já foi enviado, por isso R -1
                    break;
                case 6:
                    FillVec(&Available_R, fp, ch);
                    data += R - 1;
                    break;
                case 10:
                    FillMat(&In_Use_R, fp, ch);
                    data += R * P - 1;
                    break;
                case 22:
                    FillMat(&Required_R, fp, ch);
                    data += R * P - 1;
                    break;
                default:
                    break;
            }
            */
        }
    }

    fclose(fp);
}

void ShowData() {
    printf("\n %d", P);

    printf(" %d\n\n", R);

    for (int i = 0; i < 4; i++) {
        printf(" %d", All_R[i]);
    }
    printf("\n\n");
    for (int i = 0; i < 4; i++) {
        printf(" %d", Available_R[i]);
    }
    printf("\n\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf(" %d", In_Use_R[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf(" %d", Required_R[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    FileHandling(argv[1], "r");

    /*  Enquanto pudermos alocar recursos e rodar os processos não teremos DeadLock. */
    
    while (allocateResources()) {
        runProcess();
    }
    
    ShowData();

    checkDeadLock();

    return 0;
}
