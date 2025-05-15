#include <iostream>

using namespace std;

class Cliente{
    private:
        string nome, cpf, telefone;

    public:
        Cliente(string nome, string cpf, string telefone){
            this->nome = nome;
            this->cpf = cpf;
            this->telefone = telefone;
        }

        void dados(){
            cout << "Nome:     " << this->nome << endl;
            cout << "CPF:      " << this->cpf << endl;
            cout << "Telefone: " << this->telefone << endl;
        }

        void atualizar(string novo){
            this->telefone = novo;
            cout << "Telefone atualizado!" << endl;
        }
};

int main(){
    Cliente colono("Angelo", "123.456.789-10", "(45) 98765-4321");

    colono.dados();
    cout << endl;
    colono.atualizar("(45) 99999-8888");
    colono.dados();

    return 0;
}