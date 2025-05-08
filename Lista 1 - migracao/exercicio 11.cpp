#include <iostream>
using namespace std;

int main(){

    int x, anterior2 = 1, anterior1 = 1;;
    cout << "Digite um inteiro: ";
    cin >> x;

    if(x >= 2){
        cout << x << " primeiros termos de fibonacci:" << endl;
        cout << anterior2 << "\t" << anterior1 << "\t";
        for(int i = 2; i < x; i++){
            int fibonacci = anterior2 + anterior1;
            anterior2 = anterior1;
            anterior1 = fibonacci;
            cout << fibonacci << "\t";
        }
    } else if(x == 1){
        cout << "Primeiro termo de fibonacci:" << endl;
        cout << anterior2 << endl;
    } else{
        cout << "Valor invalido!";
    }

    return 0;
}