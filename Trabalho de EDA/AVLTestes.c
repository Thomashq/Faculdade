#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define AVL 10
#define SIZE_AVL 10000
#define MAX_RAND 100000

struct no
{
    int chave;
    int bal;
    struct no *esq;
    struct no *dir;
};
typedef struct no No;

int AlturaAVL(No *pt)
{
    if (pt == NULL)
    {
        return 0;
    }
    int hl, hr;

    if (pt->esq != NULL)
    {
        hl = AlturaAVL(pt->esq);
    }
    else
    {
        hl = 0;
    }

    if (pt->dir != NULL)
    {
        hr = AlturaAVL(pt->dir);
    }
    else
    {
        hr = 0;
    }

    if (hl > hr)
        return (hl + 1);
    else
        return (hr + 1);
}

void VerificaAVL(No *pt, bool *h)
{
    if (pt == NULL)
    {
        return;
    }
    int bal = (AlturaAVL(pt->dir) - AlturaAVL(pt->esq));
    if (bal > 1 || bal < -1)
    {
        *h = false;
    }
    VerificaAVL(pt->esq, h);
    VerificaAVL(pt->dir, h);
}

void TamanhoAVL(No *pt, int *tam)
{
    if (pt == NULL)
    {
        *tam = 0;
        return;
    }
    (*tam)++;
    if (pt->esq != NULL)
        TamanhoAVL(pt->esq, tam);
    if (pt->dir != NULL)
        TamanhoAVL(pt->dir, tam);
}

void PreOrdem(No *pt)
{
    printf("\n%d [%d] |", pt->chave, pt->bal);
    if (pt->esq != NULL)
        PreOrdem(pt->esq);
    if (pt->dir != NULL)
        PreOrdem(pt->dir);
}

void Caso1(No **pt, bool *h)
{
    No *ptu = (*pt)->esq;
    if (ptu->bal == -1)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->bal = 0;
        (*pt)->dir->bal = 0;
    }
    else
    {
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        if (ptv->bal == 1)
        {
            (*pt)->bal = 0;
            ptu->bal = -1;
        }
        else if (ptv->bal == 0)
        {
            (*pt)->bal = 0;
            ptu->bal = 0;
        }
        else
        {
            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = false;
}

void Caso2(No **pt, bool *h)
{
    No *ptu = (*pt)->dir;

    if (ptu->bal == 1)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->bal = 0;
        (*pt)->esq->bal = 0;
    }
    else
    {
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        if (ptv->bal == 1)
        {
            (*pt)->bal = -1;
            ptu->bal = 0;
        }
        else if (ptv->bal == 0)
        {
            (*pt)->bal = 0;
            ptu->bal = 0;
        }
        else
        {
            ptu->bal = 1;
            (*pt)->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = false;
}

void InserirAVL(int x, No **pt, bool *h)
{
    if (*pt == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->chave = x;
        novo->bal = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        (*pt) = novo;
        *h = true;
    }
    else
    {
        if ((*pt)->chave == x)
        {
            // printf("Elemento encontrado\n");
            *h = false;
            return;
        }
        else if (x < (*pt)->chave)
        {
            InserirAVL(x, &(*pt)->esq, h);
            if (*h) // depois de inserir tem que reajustar a altura da árvore
            {
                switch ((*pt)->bal)
                {
                case 1:
                    (*pt)->bal = 0;
                    *h = false;
                    break;
                case 0:
                    (*pt)->bal = -1;
                    break;
                case -1:
                    Caso1(pt, h);
                    break;
                }
            }
        }
        else
        {
            InserirAVL(x, &(*pt)->dir, h);
            if (*h)
            {
                switch ((*pt)->bal)
                {
                case 1:
                    Caso2(pt, h);
                    break;
                case 0:
                    (*pt)->bal = 1;
                    break;
                case -1:
                    (*pt)->bal = 0;
                    *h = false;
                    break;
                }
            }
        }
    }
}

void Caso1R(No **pt, bool *h)
{
    No *ptu = (*pt)->esq;

    if (ptu->bal <= 0)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if ((*pt)->bal == -1)
        {
            (*pt)->bal = 0;
            (*pt)->dir->bal = 0;
            *h = true;
        }
        else if ((*pt)->bal == 0)
        {
            (*pt)->bal = 1;
            (*pt)->dir->bal = -1;
            *h = false;
        }
    }
    else
    {
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        switch (ptv->bal)
        {
        case 1:
            (*pt)->bal = 0;
            ptu->bal = -1;
            break;
        case 0:
            (*pt)->bal = 0;
            ptu->bal = 0;
            break;
        case -1:
            (*pt)->bal = 1;
            ptu->bal = 0;
            break;
        }
        (*pt) = ptv;
        (*pt)->bal = 0;
        *h = true;
    }
}

void Caso2R(No **pt, bool *h)
{
    No *ptu = (*pt)->dir;

    if (ptu->bal >= 0)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;

        if ((*pt)->bal == 1)
        {
            (*pt)->bal = 0;
            (*pt)->esq->bal = 0;
            *h = true;
        }
        else
        {
            (*pt)->bal = -1;
            (*pt)->esq->bal = 1;
            *h = false;
        }
    }
    else
    {
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        switch (ptv->bal)
        {
        case 1:
            ptu->bal = 0;
            (*pt)->bal = -1;
            break;
        case 0:
            ptu->bal = 0;
            (*pt)->bal = 0;
            break;
        case -1:
            ptu->bal = 1;
            (*pt)->bal = 0;
            break;
        }
        (*pt) = ptv;
        (*pt)->bal = 0;
        *h = true;
    }
}

void Balancear(No **pt, int R, bool *h)
{
    if (*h)
    {
        if (R)
        { // Caso esteja na direita o inteiro tem 1 e passa no if
            switch ((*pt)->bal)
            {
            case 1:
                (*pt)->bal = 0;
                break;
            case 0:
                (*pt)->bal = -1;
                *h = false;
                break;
            case -1:
                Caso1R(pt, h);
                break;
            }
        }
        else
        {
            switch ((*pt)->bal)
            {
            case 1:
                Caso2R(pt, h);
                break;
            case 0:
                (*pt)->bal = 1;
                *h = false;
                break;
            case -1:
                (*pt)->bal = 0;
                break;
            }
        }
    }
}

void Trocar(No **pt, No **PaiS)
{
    int value = (*pt)->chave;
    (*pt)->chave = (*PaiS)->chave;
    (*PaiS)->chave = value;
}

void RemoverAVL(int x, No **pt, bool *h, No **ptraiz)
{
    if ((*pt) == NULL)
    {
        *h = false;
    }
    else
    {
        if (x < (*pt)->chave)
        {
            RemoverAVL(x, &(*pt)->esq, h, ptraiz);
            Balancear(pt, 0, h);
        }
        else if (x > (*pt)->chave)
        {
            RemoverAVL(x, &(*pt)->dir, h, ptraiz);
            Balancear(pt, 1, h);
        }
        else
        {
            No *aux = (*pt);
            if ((*pt)->dir == NULL)
            {
                if((*pt) == (*ptraiz)){
                    (*pt) = (*pt)->esq;
                    (*ptraiz) = (*pt);
                } else {
                    (*pt) = (*pt)->esq;
                }
                *h = true;
                free(aux);
            } else if ((*pt)->esq == NULL){
                if((*pt) == (*ptraiz)){
                    (*pt) = (*pt)->dir;
                    (*ptraiz) = (*pt);
                } else {
                    (*pt) = (*pt)->dir;
                }
                *h = true;
                free(aux);
            } else if ((*pt)->esq != NULL && (*pt)->dir != NULL){
                No *s = (*pt)->dir;
                if(s->esq == NULL){
                    s->esq = (*pt)->esq;
                    s->bal = (*pt)->bal;
                    (*pt) = s;
                    *h = true;
                } else {
                    No *PaiS;
                    while (s->esq != NULL)
                    {
                        PaiS = s;
                        s = s->esq;
                    }
                    Trocar(pt, &PaiS->esq);
                    RemoverAVL(x, &(*pt)->dir, h, ptraiz);
                }
                Balancear(pt, 1, h);
            } else {
                if((*pt) == (*ptraiz)){
                    (*ptraiz) = NULL;
                }
                free((*pt));
                *h = true;
            }
        }
    }
}

int main()
{
    for (int i = 0; i < AVL; i++)
    {
        No *ptraiz = NULL;
        bool h = false;
        srand(time(NULL));

        int array[SIZE_AVL];

        // Criação da Arvore
        for (int j = 0; j < SIZE_AVL; j++)
        {
            bool checkValue = true;
            do
            {
                checkValue = true;
                int value = (rand() % (MAX_RAND - 1)) + 1;
                for (int i = 0; i < j; i++)
                {
                    if (array[i] == value)
                    {
                        checkValue = false;
                    }
                }
                if (checkValue)
                {
                    array[j] = value;
                    InserirAVL(value, &ptraiz, &h);
                }
            } while (!checkValue);
        }
        printf("\nArvore Criada - %d.", i + 1);

        // Tamanho da Arvore Completa 10 mil nos
        int tam = 0;
        No *TamAVL = ptraiz;
        TamanhoAVL(TamAVL, &tam);
        printf("\n%d Nos", tam);

        // Checagem da Arvore AVL
        bool bal = true;
        VerificaAVL(ptraiz, &bal);
        if (bal)
            printf("\nArvore Eh AVL");

        // Removendo mil nos
        printf("\n\nRemocao dos Nos");
        for (int i = 0; i < 1000; i++)
        {
            RemoverAVL(array[i], &ptraiz, &h, &ptraiz);
        }

        // Tamanho da Arvore deve ser 9 mil
        tam = 0;
        TamAVL = ptraiz;
        TamanhoAVL(TamAVL, &tam);
        printf("\n%d Nos", tam);

        // Checagem da Arvore AVL
        bal = true;
        VerificaAVL(ptraiz, &bal);
        if (bal)
            printf("\nArvore Eh AVL");

        printf("\n");
    }
    
    return 0;
}