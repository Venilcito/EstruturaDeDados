#include <iostream>
using namespace std;

int main(){

    int a, i = 2;
    bool naoprimo = false;
    cout << "Digite um valor inteiro: ";
    cin >> a;

    do{
        if((a % i == 0) & (a != i)){
            naoprimo = true;
            break;
        }
        i++;
    }while(i < a);

    if(naoprimo){
        cout << "O numero " << a << " nao e primo";
    } else{
        cout << "O numero " << a << " e primo";
    }

    return 0;
}