#include<iostream>
#include<stdlib.h>
using namespace std;

#define ARRAY_SIZE 10

//função de ajuste seguindo max heap. assume que a subárvore já segue max heap
void troca(int A[], int i, int j){
    int aux = A[i];
    A[i] = A[j];
    A[j] = aux;
}


void max_heapify(int A[], int i, int tamHeap){
    int e = 2*i+1;       // indice do filho da esquerda
    int d = 2*i+2;       // filho da direita
    int maior;

    if (e < tamHeap && A[e] > A[i])
        maior = e;
    else
        maior = i;
    if (d < tamHeap && A[d] > A[maior])
        maior = d;
    if (maior != i)
    {
        troca(A, i, maior);
        max_heapify(A, maior, tamHeap);
    }
    
}

void constroi_max_heap(int A[], int tamHeap){
    int indice = (tamHeap-1)/2;

    for(int i = indice; i >= 0; i--){
        max_heapify(A, i, tamHeap);
    }
}

void imprime(int A[], int tamHeap){
    for(int i = 0; i < tamHeap; i++){
        cout << A[i] << " ";
    }
}

void heapsort(int A[], int tamHeap){
    constroi_max_heap(A, tamHeap);

    for(int i = tamHeap-1; i >= 0; i--){
        troca(A, 0, i);
        tamHeap--;
        max_heapify(A, 0, tamHeap);
    }
}


int main(){
    int tamHeap_A = ARRAY_SIZE;
    int A[ARRAY_SIZE] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};

    cout << "Impressao sem max_heap:  ";
    imprime(A, tamHeap_A);
    cout << endl;

    constroi_max_heap(A, tamHeap_A);

    cout << "Impressao do vetor heap: ";
    imprime(A, tamHeap_A);
    cout << endl;

    return 0;
}