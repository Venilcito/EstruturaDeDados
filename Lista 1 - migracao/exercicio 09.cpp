#include <iostream>
using namespace std;

int main(){

    float soma = 0;
    do{
        float a;
        cout << "Digite um numero: ";
        cin >> a;

        soma += a;
    } while(soma <= 100);

    cout << "Soma de todos os valores: " << soma;

    return 0;
}