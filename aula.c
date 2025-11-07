#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void maxheapify (int *A, int m, int i){
    int e, d, aux, maior;
    e = 2 * i + 1;
    d = 2 * i + 2;
    if ((e <= m) && A[e] > A[i])
        maior = e;
    else
        maior = i;
    
    if ((d<=m) && (A[d] > A[maior]))
        maior = d;

    if (maior != i) {
        aux = A[i];
        A[i] = A[maior];
        A[maior] = aux;
        maxheapify(A, m, maior);
    }
}

void build_max_heap (int *A, int n){
    for(int i = n/2; i >= 0; i--)
        maxheapify(A, n, i);
}

void heapsort2 (int *A, int n){
    int m, aux;
    build_max_heap (A, n);
    m = n-1;
    for (int i = n; i >= 1; i--){
        aux = A[0];
        A[0] = A[i];
        A[i] = aux;
        m--;
        maxheapify(A, m, 0);
    }
}

int * geraVetorDecrescente (int n) {
    int *a = malloc(sizeof(int)*n);
        for(int i = 0; i < n; i++)
            a[i] = n - i;
        return a;
}

int main (){
    int repeticoes = 15;
    int begin = 100000;
    int end = 1000000;
    int step = 10000;
    int i;
    double tempo;

    for(i = begin; i <= end; i += step){
        int *a = geraVetorDecrescente(i);
            for(int j = 0; j < repeticoes; j++){
                clock_t start = clock();
                heapsort2(a, i);
                clock_t end = clock();
                tempo = (double)(end-start)/CLOCKS_PER_SEC;
                printf("%d\t%d\t%lf\n", (j+1), i, tempo);
            }
        free(a);
    }
    return 0;
}