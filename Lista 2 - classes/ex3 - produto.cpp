#include <iostream>

using namespace std;

class Produto{
    private:
        string nome;
        float preco;
        int estoque;

    public:
        Produto(string nome, float preco, int estoque){
            this->nome = nome;
            this->preco = preco;
            this->estoque = estoque;
        }

        void dados(){
            cout << "Nome:       " << this->nome << endl;
            cout << "Preco:      " << this->preco << endl;
            cout << "Quantidade: " << this->estoque << endl;
        }

        void vender(int venda){
            if(venda > this->estoque){
                cout << "Sem estoque de \"" << this->nome << "\"! " << this->estoque << " disponiveis" << endl;
                venda = this->estoque;
            }

            float total = this->preco*(float)venda;
            this->estoque -= venda;
            cout << "Vendendo " << venda << " \"" << this->nome << "\" por R$ " << total << endl;
        }

        void repor(int reposicao){
            this->estoque += reposicao;
            cout << reposicao << " itens adicionados ao estoque de \"" << this->nome << "\"" << endl;
            cout << "Estoque atual: " << this->estoque << endl;
        }
};

int main(){
    Produto produto1("Pepsi", 5.50, 10);
    Produto produto2("Coca", 4.30, 20);

    produto1.dados();
    cout << endl;
    produto2.dados();
    cout << endl;
    produto1.vender(6);
    produto2.vender(15);
    cout << endl;
    produto1.vender(7);
    produto2.vender(6);
    cout << endl;
    produto1.repor(100);
    produto2.repor(100);

    return 0;
}