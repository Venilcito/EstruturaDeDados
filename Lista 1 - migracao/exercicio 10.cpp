#include <iostream>
using namespace std;

int main(){

    int lado;
    cout << "Digite o tamanho do lado: ";
    cin >> lado;

    cout << endl << "Triangulo:" << endl;
    for(int i = 0; i < lado; i++){
        for(int j = 0; j <= i; j++){
            cout << "*";
        }
        cout << endl;
    }

    cout << endl << "Retangulo:" << endl;
    for(int i = 0; i < lado; i++){
        for(int j = 0; j < lado; j++){
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}