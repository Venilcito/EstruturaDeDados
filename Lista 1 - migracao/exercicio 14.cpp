#include <iostream>
using namespace std;

int main(){

    int alunos;
    cout << "Digite a quantidade de alunos: ";
    cin >> alunos;

    int notas[alunos], acima = 0;
    float media = 0;

    for(int i = 1; i <= alunos; i++){
        cout << "Nota do aluno " << i << ": ";
        cin >> notas[i-1];

        media += notas[i-1];
        if(notas[i-1] >= 70){
            acima++;
        }
    }

    cout << "\nMedia da turma: " << media/(float)alunos << endl;
    cout << "Alunos acima da media: " << acima;

    return 0;
}