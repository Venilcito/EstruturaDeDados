#include <iostream>

using namespace std;

class Produto{
    private:
    string nome;
    int codigo;
    int quantidade;
    float preco;
    static int totalProdutos;

    public:
    Produto(string p_nome, int p_codigo, int p_quantidade, float p_preco){
        nome = p_nome;
        codigo = p_codigo;
        quantidade = p_quantidade;
        preco = p_preco;
        totalProdutos++;
    }

    ~Produto(){
        totalProdutos--;
    }

    void entradaEstoque(int qtd){
        quantidade += qtd;
    }

    bool saidaEstoque(int qtd){
        if(qtd > quantidade){
            return false;
        }

        quantidade -= qtd;
        return true;
    }

    float calcularValorTotal(){
        return quantidade * preco;
    }

    static int getTotalProdutos(){
        return totalProdutos;
    }
};

int Produto::totalProdutos = 0;

int main(){
    Produto prod1("Coca", 1234, 50, 2.50), prod2("Pepsi", 4321, 30, 1.25), prod3("Miotto", 9999, 1, 4999.99);

    cout << "Estoque prod1 = R$ " << prod1.calcularValorTotal() << endl;
    cout << "Estoque prod2 = R$ " << prod2.calcularValorTotal() << endl;
    cout << "Estoque prod3 = R$ " << prod3.calcularValorTotal() << endl << endl;

    prod1.entradaEstoque(50);
    prod2.entradaEstoque(70);
    prod3.entradaEstoque(2);

    prod1.saidaEstoque(60);
    prod2.saidaEstoque(80);
    prod3.saidaEstoque(1);

    cout << "Estoque prod1 = R$ " << prod1.calcularValorTotal() << endl;
    cout << "Estoque prod2 = R$ " << prod2.calcularValorTotal() << endl;
    cout << "Estoque prod3 = R$ " << prod3.calcularValorTotal() << endl << endl;

    cout << "Produtos criados: " << Produto::getTotalProdutos() << endl;
}