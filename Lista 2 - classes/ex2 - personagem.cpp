#include <iostream>

using namespace std;

class Personagem{
    private:
        string nome;
        int vida, ataque, defesa;

    public:
        Personagem(string nome, int vida, int ataque, int defesa){
            this->nome = nome;
            this->vida = vida;
            this->ataque = ataque;
            this->defesa = defesa;
        }

        void status(){
            bool estavivo = true;
            if(this->vida <= 0){
                this->vida = 0;
                estavivo = false;
            }

            cout << "Nome:   " << this->nome << endl;
            cout << "Vida:   " << this->vida << endl;
            cout << "Ataque: " << this->ataque << endl;
            cout << "Defesa: " << this->defesa << endl;
            estavivo ? cout << "O personagem esta vivo" << endl : cout << "O personagem esta morto!" << endl;
        }

        int dano(int golpe){
            if(this->defesa == 0){
                this->vida -= golpe;
            } else{
                this->defesa -= golpe;

                if(this->defesa < 0){
                    this->vida += defesa;
                    this->defesa = 0;
                }
            }

            return this->vida;
        }

        int golpe(Personagem *novo){
            int dano = novo->dano(this->ataque);

            return dano;
        }      
};

int main(){
    Personagem cara1("Scorpion", 100, 50, 10);
    Personagem cara2("Subzero", 100, 50, 5);

    cara1.status();
    cout << endl;
    cara2.status();

    cout << endl << "Scorpion atacou!" << endl;
    cara1.golpe(&cara2);
    cara2.status();

    cout << endl<< "Subzero atacou!" << endl;
    cara2.golpe(&cara1);
    cara1.status();

    return 0;
}