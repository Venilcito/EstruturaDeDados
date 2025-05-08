#include <iostream>
using namespace std;

int main(){
    
    int x;
    cout << "Digite um inteiro: ";
    cin >> x;

    x%2 == 0 ? cout << "O numero e par" : cout << "O numero e impar";

    return 0;
}