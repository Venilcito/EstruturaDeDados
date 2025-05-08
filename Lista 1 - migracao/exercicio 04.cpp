#include <iostream>
using namespace std;

int main(){

    double a, b;
    char operacao;

    cout << "Digite uma expressao (a + b, a - b, a * b, a / b):" << endl;
    cin >> a >> operacao >> b;

    switch(operacao){
        case '+':
            cout << "Soma = " << a + b;
            break;
        case '-':
            cout << "Subtracao = " << a - b;
            break;
        case '*':
            cout << "Multiplicacao = " << a * b;
            break;
        case '/':
            cout << "Divisao = " << a / b;
            break;
        default:
            cout << "Operacao invalida!";
    }

    return 0;
}