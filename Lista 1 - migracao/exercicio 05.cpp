#include <iostream>
using namespace std;

int main(){

    int mes;
    string meses[] = {"janeiro", "fevereiro", "marco", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
    cout << "Digite o numero de um mes: ";
    cin >> mes;

    switch(mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            cout << "O mes de " << meses[mes-1] << " tem 31 dias";
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            cout << "O mes de " << meses[mes-1] << " tem 30 dias";
            break;
        case 2:
            cout << "O mes de fevereiro tem 28 dias";
            break;
        default:
            cout << "Mes invalido!";
    }

    return 0;
}