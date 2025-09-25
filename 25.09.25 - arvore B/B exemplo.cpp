#include <iostream>
using namespace std;
// nao sei quanto codigo tinha aqui pra cima pois cheguei 1 hora dps na aula

class arvoreb{
// .....
//metodo para inserçao
void inserirNaoCheia(node_b *x, int key){
    int i = x->n - 1;

    if(x->folha){
        while(i >= 0 && key < x->chaves[i]){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }

        x->chaves[i+1] = key;
        x->n = x->n+1;
    } else{
        while(i >= 0 && key < x->chaves[i]){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }

        i++;
        if(x->filhos[i]->n == ordem){
            split(x, i);
            if(key > x->chaves[i]) i++;
        }

        inserirNaoCheia(x->filhos[i], key);
    }
}

void percurso(node_b *x){
    int i;

    for(i = 0; i < x->n; i++){
        if(!x->folha) percurso(x->filhos[i]);
        cout << " " << x->chaves[i];
    }

    if(!x->folha) percurso(x->filhos[i]);
}

public:

void insere(int key){
    if(raiz->n == ordem){     // inserção na raiz
        node_b *s = new node_b(false);
        s->filhos[0] = raiz;
        raiz = s;

        split(s, 0);
        inserirNaoCheia(s, key);
    } else{
        inserirNaoCheia(raiz, key);
    }
}

void percorre(){
    if(raiz != nullptr) percurso(raiz);
}

arvoreb(){
    raiz = new node_b(true);
}

};

int main(){
    arvoreb t;
    t.insere(10);
    t.insere(20);
    t.insere(5);
    t.insere(6);
    t.insere(12);

    t.percorre();
    cout << endl;
}