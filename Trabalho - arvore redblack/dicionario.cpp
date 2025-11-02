#include <iostream>
using namespace std;

#define RED 1
#define BLACK 0

class rb_no{
    public:
    string palavra;
    string significado;
    bool cor;               // false preto, true vermelho
    rb_no* dir;
    rb_no* esq;
    rb_no* father;

    rb_no(string palavra, string significado){
        this->palavra = palavra;
        this->significado = significado;
        this->dir = NULL;
        this->esq = NULL;
        this->father = NULL;
        this->cor = true;
    }
};

class rb_tree{
    public:
    rb_no* root;
    rb_no* NIL;

    rb_tree(){
        this->NIL = new rb_no("NIL", "NIL");
        this->NIL->cor = false;
        this->root = NIL;
    }

    void rotacao_direita(rb_no* x){
        rb_no* y = x->esq;
        x->esq = y->dir;

        if(y->dir != NIL){
            y = x;
        }

        y->father = x->father;

        if(x->father == NIL){
            root = y;
        }else{
            if(x == x->father->dir){
                x->father->dir = y;
            }else{
                x->father->esq = y;
            }
        }

        y->dir = x;
        x->father = y;
    }

    void rotacao_esquerda(rb_no* x){
        rb_no* y = x->dir;
        x->dir = y->esq;

        if(y->esq != NIL){
            y = x;
        }

        y->father = x->father;

        if(x->father == NIL){
            root = y;
        }else{
            if(x == x->father->esq){
                x->father->esq = y;
            }else{
                x->father->dir = y;
            }
        }

        y->esq = x;
        x->father = y;
    }
    
    void fix_insert(rb_no* no){
        while(no->father->cor == true){ // vermelho
            // caso 1 tio vermelho
            //rb_no* tio = no->father->father->esq;
            if(no->father == no->father->father->esq){
                rb_no* tio = no->father->father->dir;
                if(tio->cor == true){ // tio é vermelho!!!!!!! (Caso 1)
                    no->father->cor = false;
                    tio->cor = false;
                    no->father->father->cor = true;
                    no = no->father->father;
                }else{
                    if(no == no->father->dir){ // caso2: no é filho direito, roda e vira caso 3
                        no = no->father;
                        rotacao_esquerda(no);
                    }
                    // caso 3 tio preto e no é filho esquerdo
                    no->father->cor = false;
                    no->father->father->cor = true;
                    rotacao_direita(no->father->father);
                }
            }else{
                // espelhamento dos casos acima (lado direito)
                rb_no* tio = no->father->father->esq;
                if(tio->cor == true){ // vermelho
                    no->father->cor = false;
                    tio->cor = false;
                    no->father->father->cor = true;
                    no = no->father->father;
                }else{
                    if(no == no->father->esq){
                        no = no->father;
                        rotacao_direita(no);
                    }
                    no->father->cor = false;
                    no->father->father->cor = true;
                    rotacao_esquerda(no->father->father);
                }
            }
        }

        root->cor = false;
    }

    void rb_insert(string palavra, string significado){
        rb_no* new_node = new rb_no(palavra, significado);

        rb_no* y = NIL;
        rb_no* x = root;

        //inserção
        while(x != NIL){
            y = x;
            if(new_node->palavra < x->palavra){
                x = x->esq;
            }else{
                x = x->dir;
            }
        }

        new_node->father = y;
        if(y == NIL){
            //new_node->cor = false; // faz a raíz ficar preta
            root = new_node;
        }else if(new_node->palavra < y->palavra){
            y->esq = new_node;
        }else{
            y->dir = new_node;
        }

        new_node->esq = NIL;
        new_node->dir = NIL;
        new_node->cor = true;

        // rodar a árvore e fazer pinturas
        fix_insert(new_node);
    }

    // Acha o mínimo de uma sub árvore
    rb_no* tree_minimum(rb_no* node){
        while(node->esq != NIL){
            node = node->esq;
        }
        cout << "MINIMUM: " << node->palavra << endl;
        return node;
    }

    // trocar dois nós de lugar sem cagar tudo
    void switch2(rb_no* x, rb_no* y){
        if(x->father == NIL){
            root = y;
        }else if(x == x->father->esq){
            x->father->esq = y;
        }else{
            x->father->dir = y;
        }

        y->father = x->father;
    }

    void rb_remove(string palavra){        
        rb_no* z = rb_search(palavra);
        rb_no* y = z;
        rb_no* x = NIL;
        bool y_original_color = y->cor;
        
        if(z->esq == NIL){
            x = z->dir;
            switch2(z, z->dir);
        }else if(z->dir == NIL){
            x = z->esq;
            switch2(z, z->esq);
        }else{
            y = tree_minimum(z->dir);
            y_original_color = y->cor;
            x = y->dir;
            if(y->father == z){
                x->father = y;
            }else{
                switch2(y, y->dir);
                y->dir = z->dir;
                y->dir->father = y;
            }
            switch2(z, y);
            y->esq = z->esq;
            y->esq->father = y;
            y->cor = z->cor;
        }
        
        if(y_original_color == BLACK){
            fix_delete(x);
        }
    }

    void fix_delete(rb_no* no){
        while(no != root && no->cor == BLACK){
            if(no == no->father->esq){
                rb_no* irmao = no->father->dir;

                if(irmao->cor == RED){
                    // caso 1
                    irmao->cor = BLACK;
                    no->father->cor = RED;
                    rotacao_esquerda(no->father);
                    irmao = no->father->dir;
                }

                if(irmao->esq->cor == BLACK && irmao->dir->cor == BLACK){
                    // caso 2
                    irmao->cor = RED;
                    no = no->father;
                }else{
                    if(irmao->dir->cor == BLACK){
                        // caso 3
                        irmao->esq->cor = BLACK;
                        irmao->cor = RED;
                        rotacao_direita(irmao);
                        irmao = no->father->dir;
                    }
                    // caso 4
                    irmao->cor = no->father->cor;
                    no->father->cor = BLACK;
                    irmao->dir->cor = BLACK;
                    rotacao_esquerda(no->father);
                    no = root;
                }
            }else{
                rb_no* irmao = no->father->esq;

                if(irmao->cor == RED){
                    irmao->cor = BLACK;
                    no->father->cor = RED;
                    rotacao_esquerda(no->father);
                    irmao = no->father->esq;
                }

                if(irmao->dir->cor == BLACK && irmao->esq->cor == BLACK){
                    irmao->cor = RED;
                    no = no->father;
                }else{
                    if(irmao->esq->cor == BLACK){
                        irmao->dir->cor = BLACK;
                        irmao->cor = RED;
                        rotacao_esquerda(irmao);
                        irmao = no->father->esq;
                    }

                    irmao->cor = no->father->cor;
                    no->father->cor = BLACK;
                    irmao->esq->cor = BLACK;
                    rotacao_direita(no->father);
                    no = root;
                }
            }
        }
        no->cor = BLACK;
    }

    rb_no* rb_search(string palavra, rb_no* current){
        if(current == NIL){ return NIL; }
    
        if(current->palavra == palavra){
            return current;
        }else{
            if(current->palavra > palavra){
                return rb_search(palavra, current->esq);
            }else{
                return rb_search(palavra, current->dir);
            }
        }
    }

    rb_no* rb_search(string palavra){
        return rb_search(palavra, root);
    }

};

int main(){
    
    rb_tree arvore = rb_tree();
    arvore.rb_insert("0", "significado");
    arvore.rb_insert("2", "significado");
    arvore.rb_insert("1", "significado");
    arvore.rb_insert("4", "significado");
    arvore.rb_insert("3", "significado");
    arvore.rb_insert("5", "significado");
    rb_no* atual = arvore.root;
    
    cout << "esquerda: " << endl;
    while(atual != NULL){
        cout << atual->palavra << " | Vermelho? = ";
        cout << atual->cor << endl;
        if(atual->esq != NULL){
            atual = atual->esq;
        }else{
            atual = NULL;
        }
    }
    
    cout << "Direita" << endl;
    atual = arvore.root;
    while(atual != NULL){
        cout << atual->palavra << " | Vermelho? = ";
        cout << atual->cor << endl;
        if(atual->dir != NULL){
            atual = atual->dir;
        }else{
            atual = NULL;
        }
    }

    //rb_no* escolha = arvore.rb_search("2");
    //cout << escolha->palavra << endl;
    
    cout << arvore.root->dir->esq->palavra << endl;
    cout << arvore.root->dir->esq->cor << endl;
    
    arvore.rb_remove("2");
    
    cout << arvore.root->dir->esq->palavra << endl;
    cout << arvore.root->dir->esq->cor << endl;

    return 0;
}