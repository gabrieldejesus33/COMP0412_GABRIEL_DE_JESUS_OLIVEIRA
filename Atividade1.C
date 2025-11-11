#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void copiaVetor(int *origem, int *destino, int n) {
    memcpy(destino, origem, n * sizeof(int));
}

void preencheAleatorio(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n * 10);
    }
}

void preencheCrescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void preencheDecrescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - 1 - i;
    }
}

int estaOrdenado(int *A, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void insertion(int *A, int n) {
    int i, j, key;
    for (j = 1; j < n; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort_recursivo(int *A, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort_recursivo(A, p, q);
        mergeSort_recursivo(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void mergesort2(int *A, int n) {
    mergeSort_recursivo(A, 0, n - 1);
}

int partition(int *A, int p, int r) {
    int pivot = A[r];
    int i = (p - 1);
    
    for (int j = p; j <= r - 1; j++) {
        if (A[j] < pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return (i + 1);
}

void quickSort_recursivo(int *A, int p, int r) {
    if (p < r) {
        int pivot_index = p + rand() % (r - p + 1);
        swap(&A[pivot_index], &A[r]);
        int q = partition(A, p, r);
        
        quickSort_recursivo(A, p, q - 1);
        quickSort_recursivo(A, q + 1, r);
    }
}
void quicksort(int *A, int n) {
    quickSort_recursivo(A, 0, n - 1);
}

const int TAMANHOS[] = {1000, 10000, 50000, 100000};
const int NUM_TAMANHOS = sizeof(TAMANHOS) / sizeof(TAMANHOS[0]);

typedef enum { ALEATORIO, CRESCENTE, DECRESCENTE } TipoVetor;

void executarTeste(void (*funcaoOrdenacao)(int*, int), int *vetorOriginal, int n, const char* nomeAlgoritmo) {
    
    int *vetorParaOrdenar = (int*)malloc(n * sizeof(int));
    if (vetorParaOrdenar == NULL) {
        printf("Falha na alocacao de memoria!\n");
        exit(1);
    }
    copiaVetor(vetorOriginal, vetorParaOrdenar, n);
    
    clock_t inicio, fim;
    double tempoCPU;
    
    inicio = clock();
    funcaoOrdenacao(vetorParaOrdenar, n);
    fim = clock();
    
    tempoCPU = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    
    if (estaOrdenado(vetorParaOrdenar, n)) {
        printf("%-12s %-12.3fs\n", nomeAlgoritmo, tempoCPU);
    } else {
        printf("%-12s FALHOU A ORDENACAO\n", nomeAlgoritmo);
    }
    
    free(vetorParaOrdenar);
}


int main() {
    srand(time(NULL)); 
    
    int *vetorMestre = NULL;

    for (int tipo = ALEATORIO; tipo <= DECRESCENTE; tipo++) {
        
        const char* nomeTipo;
        switch(tipo) {
            case ALEATORIO: nomeTipo = "Vetor Aleatorio"; break;
            case CRESCENTE: nomeTipo = "Vetor Crescente"; break;
            case DECRESCENTE: nomeTipo = "Vetor Decrescente"; break;
        }

        printf("- TIPO DE ENTRADA: %s\n", nomeTipo);

        for (int i = 0; i < NUM_TAMANHOS; i++) {
            int n = TAMANHOS[i];
            printf("\nTestando com N = %d \n\n", n);
            printf("Algoritmo    Tempo de Execucao\n\n");
            
            vetorMestre = (int*)malloc(n * sizeof(int));
            if (vetorMestre == NULL) {
                printf("Falha na alocacao de memoria!\n");
                return 1;
            }
            
            switch(tipo) {
                case ALEATORIO: preencheAleatorio(vetorMestre, n); break;
                case CRESCENTE: preencheCrescente(vetorMestre, n); break;
                case DECRESCENTE: preencheDecrescente(vetorMestre, n); break;
            }
            
            executarTeste(insertion, vetorMestre, n, "Insertion");
            executarTeste(mergesort2, vetorMestre, n, "Mergesort");
            executarTeste(quicksort, vetorMestre, n, "Quicksort");
            
            printf("\n");
            
            free(vetorMestre);
        }
    }
    
    return 0;
}
