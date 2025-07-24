#include <iostream>
#include <algorithm>
using namespace std;

class avl_node{
    public:
    int key;
    avl_node* esq;
    avl_node* dir;
    int altura;
    
    avl_node(int key){
        this->key = key;
        this->altura = 1;
        this->esq = NULL;
        this->dir = NULL;
    }
};

class AVL_tree{
    public:
    avl_node* raiz;

    AVL_tree(){
        this->raiz = NULL;
    }

    public:
    int height(avl_node* no){
        if(no == 0){
            return 0;
        }
        return no->altura;
    }

    int fator_balanceamento(avl_node* no){
        if(no == NULL){
            return 0;
        }
        return height(no->esq) - height(no->dir);
    }

    avl_node* rotacao_direita(avl_node* y){
        avl_node* x = y->esq;
        avl_node* T2 = x->dir;

        x->dir = y;
        y->esq = T2;

        y->altura = max(height(y->esq), height(y->dir)) + 1;
        x->altura = max(height(x->esq), height(x->dir)) + 1;

        return x;
    }

    avl_node* rotacao_esquerda(avl_node* x){
        avl_node* y =  x->dir;
        avl_node* T2 = y->esq;

        y->esq = x;
        x->dir = T2;

        y->altura = max(height(y->esq), height(y->dir)) + 1;
        x->altura = max(height(x->esq), height(x->dir)) + 1;

        return y;
    }

    avl_node* inserir(avl_node *no, int key){
        if(no == NULL){
            return new avl_node(key);
        }

        if(key < no->key){
            no->esq = inserir(no->esq, key);
        }else if(key > no->key){
            no->dir = inserir(no->dir, key);
        }else{
            return no;
        }
        no->altura = 1 + max(height(no->esq), height(no->dir));

        int fb = fator_balanceamento(no);
        if(fb > 1 && fator_balanceamento(no->esq) >= 0){          //caso 1.1 -> esq esq
            return rotacao_direita(no);
        }
        if(fb < -1 && fator_balanceamento(no->dir) <= 0){         //caso 2.1 -> dir dir
            return rotacao_esquerda(no);
        }
        if(fb > 1 && fator_balanceamento(no->esq) < 0){           //caso 1.2 -> esq dir
            no->esq = rotacao_esquerda(no->esq);
            return rotacao_direita(no);
        }
        if(fb < -1 && fator_balanceamento(no->dir) > 0){          //caso 2.2 -> dir esq
            no->dir = rotacao_direita(no->dir);
            return rotacao_esquerda(no);
        }

        return no;
    }

    void imprimir(avl_node* no){
        // impressão em ordem: subárvore esq -> raiz -> subárvore dir
        if(no != NULL){
            imprimir(no->esq);
            cout << no->key << " ";
            imprimir(no->dir);
        }
    }

    void inserir(int key){
        raiz = inserir(raiz, key);
    }
};

int main(){
    AVL_tree arvore;

    /*
    srand(time(NULL));
    for(int i = 0; i < 2000; i++){
        arvore.inserir(rand() % 10000);
    }
    */

    arvore.inserir(30);
    arvore.inserir(40);
    arvore.inserir(50);
    arvore.inserir(20);

    arvore.imprimir(arvore.raiz);
    cout << endl;

    return 0;
}