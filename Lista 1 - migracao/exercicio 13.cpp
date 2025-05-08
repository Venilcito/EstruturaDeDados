#include <iostream>
using namespace std;

int main(){

    double vetor[10];
    cout << "Digite 10 numeros: ";
    for(int i = 0; i < 10; i++){
        cin >> vetor[i];
    }

    cout << "Ordem inversa:     ";
    for(int i = 9; i >= 0; i--){
        cout << vetor[i] << " ";
    }

    return 0;
}