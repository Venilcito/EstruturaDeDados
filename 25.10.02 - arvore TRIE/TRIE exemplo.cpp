#include <iostream>
#include <cstring>
using namespace std;

#define ALFABETO 26
#define ASCII 65        // A maiúsculo na tabela ascii

struct no{
    no *p[ALFABETO];
    char chave[20];
};

// função pra criar o nó vazio
no *criaNo(){
    no *n = new no;

    for(int i = 0; i < ALFABETO; i++) n->p[i] = NULL;
    
    n->chave[0] = '\0';
    return n;
}

// função pra imprimir a árvore em ordem
void emordem(no *n){
    int j = 0;

    if(n != NULL){
        for(int i = 0; i < ALFABETO; i++){
            if(n->p[i] != NULL){
                j = i + ASCII;
                cout << (char)j << " ";
                emordem(n->p[i]);
            }
        }
    }
}

int char_to_index(char chr){
    char c = toupper(chr);
    return c - ASCII;
}

// função de inclusão de um nó
void incluir(no *no, const char *chave){
    int nivel, indice;
    int tamanho = strlen(chave);

    for(nivel = 0; nivel < tamanho; nivel++){
        indice = char_to_index(chave[nivel]);
        if(no->p[indice] == NULL) no->p[indice] = criaNo();
        no = no->p[indice];
    }

    for(int i = 0; i < tamanho; i++) no->chave[i] = chave[i];
}

// função que retorna o token de uma string - separa por espaço
char *get_token(const char *str, int *indice){
    char *token = (char *) malloc(sizeof(char)*20);

    int i = 0;
    while(str[*indice] != '\0' && str[*indice] != ' '){
        token[i] = str[*indice];
        i++;
        (*indice)++;
    }

    token[i] = '\0';
    (*indice)++;
    return token;
}

// a tal
no *monta_arvore(const char *str){
    no* raiz = NULL;
    int i = 0;
    raiz = criaNo();

    while(str[i] != '\0') incluir(raiz, get_token(str, &i));
    return raiz;
}

int noLivre(no *n){
    for(int i = 0; i < ALFABETO; i++){
        if(n->p[i]) return 0;
    }

    return 1;
}

int excluir(no *n, const char *chave, int nivel, int tamanho){
    if(n != NULL){
        if(nivel == tamanho){
            if(strcmp(n->chave, chave)) n->chave[0] = '\0';
            if(noLivre(n)) return 1;
            return 0;
        } else{
            int indice = char_to_index(chave[nivel]);
            if(excluir(n->p[indice], chave, nivel+1, tamanho)){
                free(n->p[indice]);
                return ((n->chave[0] != '\0') && noLivre(n));
            }
        }
    }
    return 0;
}

int main(){
    no* raiz = NULL;
    char entrada[] = "casa carro bola carta\0";
    //char entrada[] = "tini esquilo venilso varas mattsu";
    raiz = monta_arvore(entrada);
    
    cout << "Percurso da arvore: ";
    emordem(raiz);
    cout << endl;

    cout << "excluindo chave \"carro\"" << endl;
    excluir(raiz, "carro", 0, strlen("carro"));

    cout << "Novo percurso da arvore: ";
    emordem(raiz);
    cout << endl;
}