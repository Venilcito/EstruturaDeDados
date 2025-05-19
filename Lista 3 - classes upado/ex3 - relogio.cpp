#include <iostream>

using namespace std;

class Relogio24Horas{
    private:
    int hora, minuto, segundo;

    public:
    Relogio24Horas(){
        hora = 0;
        minuto = 0;
        segundo = 0;
    }

    void ImprimeHora(){
        cout << hora << ":" << minuto << ":" << segundo << endl;
    }

    void IncrementaSegundo(){
        segundo++;

        if(segundo >= 60){
            segundo = 0;
            minuto++;
            
            if(minuto >= 60){
                minuto = 0;
                hora++;

                if(hora >= 24){
                    hora = 0;
                }
            }
        }
    }

    bool ehIgual(Relogio24Horas outro){
        return outro.hora == hora && outro.minuto == minuto && outro.segundo == segundo;
    }

    void setTempo(int h, int m, int s){
        if(h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59){
            cout << "Valor invalido inserido" << endl;
            return;
        }
        hora = h;
        minuto = m;
        segundo = s;
    }
};

int main(){
    Relogio24Horas relogio1, relogio2;
    relogio1.setTempo(23, 59, 59);

    relogio1.ImprimeHora();
    cout << "+1 segundo" << endl;
    relogio1.IncrementaSegundo();
    relogio1.ImprimeHora();

    if(relogio1.ehIgual(relogio2)){
        cout << "Os dois relogios estao iguais" << endl;
    } else{
        cout << "Os dois relogios nao estao iguais" << endl;
    }
}