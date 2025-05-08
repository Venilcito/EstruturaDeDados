#include <iostream>
using namespace std;

int main(){

    srand(time(NULL));
    int secreto = rand() % 100, tentativas = 0, palpite = 0;
    
    cout << "Descubra o numero secreto entre 1 e 100!" << endl;
    while(palpite != secreto){
        tentativas++;
        cout << "Palpite: ";
        cin >> palpite;

        if(palpite > secreto){
            cout << "O numero e menor que " << palpite << endl;
        } else if(palpite < secreto){
            cout << "O numero e maior que " << palpite << endl;
        }
    }

    cout << "Voce acertou! O numero e " << secreto << endl;
    cout << "Voce encontrou o numero secreto em " << tentativas << " tentativas";

    return 0;
}