#include <iostream>
#define MAX 100
using namespace std;

class Pilha{
private:
    int dados[MAX];
    int topo;

public:
    Pilha(){
        topo = -1;
    }
    
    void binario(int valor){
        if(valor == 0){
            push(0);
        }else{
            while(valor > 0){
                push(valor % 2);
                valor /= 2;
            }
        }
    }

    void push(int valor){
        topo++;
        dados[topo] = valor;
    }

    void mostrar(){
        if (topo == -1){
            cout << "Pilha vazia!" << endl;
        } else{
            for (int i = topo; i >= 0; i--){
                cout << dados[i];
            }
            cout << endl;
        }
    }
};

int main(){
    Pilha p;
    p.binario(3421);
    
    cout << "Numero em binario: ";
    p.mostrar();
    return 0;
}