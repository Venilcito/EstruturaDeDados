#include <iostream>
using namespace std;

int main(){

    int tam;
    cout << "Digite o tamanho do vetor: ";
    cin >> tam;
    int vetor[tam];

    cout << "Digite os " << tam << " elementos: ";
    for(int i = 1; i <= tam; i++){
        cin >> vetor[i-1];
    }

    int maior = vetor[0], menor = vetor[0];
    for(int i = 0; i < tam; i++){
        if(vetor[i] > maior){
            maior = vetor[i];
        }
        if(vetor[i] < menor){
            menor = vetor[i];
        }
    }
    cout << "\nMaior valor: " << maior << endl;
    cout << "Menor valor: " << menor << endl;

    return 0;
}