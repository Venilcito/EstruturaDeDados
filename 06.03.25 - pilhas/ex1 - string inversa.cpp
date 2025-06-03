#include <iostream>
#define MAX 100
using namespace std;

class Pilha{
private:
    char dados[MAX];
    int topo;

public:
    Pilha() {
        topo = -1;
    }

    void push(string valor){
        for(char c : valor){
            if (topo == MAX - 1){
                cout << "Pilha cheia!" << endl;
                break;
            }
            topo++;
            dados[topo] = c;
        }
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
    p.push("abcdefghijklmnopqrstuvwxyz");
    
    cout << "Palavra invertida: ";
    p.mostrar();
    return 0;
}