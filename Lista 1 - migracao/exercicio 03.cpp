#include <iostream>
using namespace std;

int main(){

    float a, b, c;
    cout << "Digite 3 numeros: ";
    cin >> a >> b >> c;

    if((a > b) & (a > c)){
        cout << "O numero " << a << " e o maior";
    } else if((b > a) & (b > c)){
        cout << "O numero " << b << " e o maior";
    } else if((c > a) & (c > b)){
        cout << "O numero " << c << " e o maior";
    } else{
        cout << "Os tres numeros sao iguais";
    }

    return 0;
}