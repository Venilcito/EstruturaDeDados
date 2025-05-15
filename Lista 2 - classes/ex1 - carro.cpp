#include <iostream>

using namespace std;

class Carro{
    
    private:
        string marca, modelo;
        int ano, velocidade;
    
    public:
        Carro(string marca, string modelo, int ano){
            this->marca = marca;
            this->modelo = modelo;
            this->ano = ano;
            this->velocidade = 0;
        }
        
        void dados(){
            cout << "Marca:      " << this->marca << endl;
            cout << "Modelo:     " << this->modelo << endl;
            cout << "Ano:        " << this->ano << endl;
            cout << "Velocidade: " << this->velocidade << endl;
        }
        
        int acelerar(int tempo, int aceleracao){
            this->velocidade += tempo*aceleracao;
            return this->velocidade;
        }
        
        int freiar(int tempo, int aceleracao){
            this->velocidade -= tempo*aceleracao;
            if(velocidade < 0){
                return 0;
            } else{
                return this->velocidade;
            }
        }
};

int main()
{
    Carro batmovel("Volkswagen", "Fusca", 1984);
    batmovel.dados();
    int vel = batmovel.acelerar(5, 2);
    cout << "Velocidade: " << vel << endl;
    vel = batmovel.freiar(2, 3);
    cout << "Velocidade: " << vel << endl;

    return 0;
}