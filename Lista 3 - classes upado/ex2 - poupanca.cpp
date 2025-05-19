#include <iostream>

using namespace std;

class ContaDePoupanca{
    static double taxaDeJurosAnual;

    private:
    double saldoDaPoupanca;

    public:
    static void modifiqueTaxaDeJuros(double juros){
        taxaDeJurosAnual = juros / 100;
    }

    static void calculeRendimentoMensal(ContaDePoupanca *poupanca){
        poupanca->saldoDaPoupanca += poupanca->saldoDaPoupanca * (taxaDeJurosAnual/12.0);
    }

    void setSaldo(double saldo){
        saldoDaPoupanca = saldo;
    }

    double getSaldo(){
        return saldoDaPoupanca;
    }
};

double ContaDePoupanca::taxaDeJurosAnual = 0;

int main(){
    ContaDePoupanca poupador1, poupador2;

    poupador1.setSaldo(2000);
    poupador2.setSaldo(3000);

    cout << "Taxa de Juros Anual = 6%" << endl;
    ContaDePoupanca::modifiqueTaxaDeJuros(6);
    ContaDePoupanca::calculeRendimentoMensal(&poupador1);
    ContaDePoupanca::calculeRendimentoMensal(&poupador2);
    cout << "Saldo 1: R$ " << poupador1.getSaldo() << endl;
    cout << "Saldo 2: R$ " << poupador2.getSaldo() << endl;

    cout << endl << "Taxa de Juros Anual = 8%" << endl;
    ContaDePoupanca::modifiqueTaxaDeJuros(8);
    ContaDePoupanca::calculeRendimentoMensal(&poupador1);
    ContaDePoupanca::calculeRendimentoMensal(&poupador2);
    cout << "Saldo 1: R$ " << poupador1.getSaldo() << endl;
    cout << "Saldo 2: R$ " << poupador2.getSaldo() << endl;

    return 0;
}