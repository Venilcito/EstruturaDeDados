#include <iostream>
using namespace std;

int main(){

    int a;
    cout << "Digite um valor inteiro: ";
    cin >> a;
    int fatorial = a;

    while(a > 1){
        fatorial *= a - 1;
        a--;
    }

    cout << "Fatorial = " << fatorial;

    return 0;
}