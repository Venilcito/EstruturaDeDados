#include <iostream>

using namespace std;

class Conta{
    private:
        int numero;
        string titular;
        float saldo, inicial;

        int operacao = 0;
        float regV[1000];
        bool regS[1000];

    public:
        Conta(int numero, string titular, float saldo){
            this->numero = numero;
            this->titular = titular;
            this->saldo = saldo;
            this->inicial = saldo;
        }

        void depositar(float deposito){
            if(deposito == 0){return;}
            this->saldo += deposito;

            regV[operacao] = deposito;
            regS[operacao] = true;
            operacao++;
        }

        void sacar(float saque){
            if(saque == 0){return;}

            bool sucesso = true;
            if(saque > this->saldo){
                sucesso = false;
            } else{
                this->saldo -= saque;
            }

            regV[operacao] = 0-saque;
            regS[operacao] = sucesso;
            operacao++;
        }

        void extrato(){
            cout << "Extrato da conta N. " << this->numero << " | " << this->titular << endl;

            for(int i = 0; i < operacao; i++){
                cout << endl << "Operacao " << i+1 << " | ";

                if(regV[i] > 0){
                    this->inicial += regV[i];
                    cout << "Deposito: R$ " << regV[i] << endl;
                    cout << "Saldo atual: R$ " << this->inicial << endl;
                } else if(regV[i] < 0 && regS[i]){
                    this->inicial += regV[i];
                    cout << "Saque: R$ " << regV[i] * -1 << endl;
                    cout << "Saldo atual: R$ " << this->inicial << endl;
                } else{
                    cout << "Tentativa de saque: R$ " << regV[i] * -1 << endl;
                    cout << "Saldo insuficiente! R$ " << this->inicial << endl;
                }
            }

            cout << endl << "Fim do registro" << endl;
        }

};

int main(){
    Conta banco(1234, "Venilso", 0);

    banco.depositar(1000);
    banco.sacar(500);
    banco.sacar(600);
    banco.extrato();

    return 0;
}