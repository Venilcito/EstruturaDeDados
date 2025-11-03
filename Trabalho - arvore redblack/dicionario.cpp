#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

#define RED 1
#define BLACK 0

// Cores do front do esquilo
#define CLEAR "\033[H\033[2J"
#define RESET "\033[0m"
#define REVERSE "\033[7m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define BG_BLUE "\033[44m"
#define BG_WHITE "\033[107m"
#define BG_WHITE_2 "\033[47m"
#define BG_PLAYER "\033[107m"
#define BG_BLACK "\033[40m"
#define BG_BBLACK "\033[100m"
#define BG_GREEN "\033[42m"
#define BG_RED "\033[41m"
#define FG_GREEN "\033[92m"
#define FG_RED "\033[91m"
#define FG_WHITE "\033[37m"
#define FG_BLACK "\033[30m"

// USADO NO MENU BONITINHO
void clrscr() {
    printf(CLEAR);
}

// CLASSE DO NÓ DA ARVORE
class rb_no{
    public:
    string palavra;
    string significado;
    bool cor;               // false preto, true vermelho, tipo um is_red, mas agnt acaba usando o RED e BLACK do define
    rb_no* dir;
    rb_no* esq;
    rb_no* father;

    // Construtor, deixa tudo null msm, a cor inicial qeu é red
    rb_no(string palavra, string significado){
        this->palavra = palavra;
        this->significado = significado;
        this->dir = NULL;
        this->esq = NULL;
        this->father = NULL;
        this->cor = RED;
    }
};

// Classe da árvore red-velvet por si só
class rb_tree{
    public:
    rb_no* root;
    rb_no* NIL; // Esse nil salvou agnt em alguns casos

    // Construct serve mais pra fazer o nil existir no início
    rb_tree(){
        this->NIL = new rb_no("NIL", "NIL");
        this->NIL->cor = false;
        this->NIL->esq = this->NIL;
        this->NIL->dir = this->NIL;
        this->NIL->father = this->NIL;

        this->root = NIL; // Root PRECISA ser nil, se n vai crashar
    }

    // Rotação a direita de acordo com o livro da usp
    void rotacao_direita(rb_no* x){
        rb_no* y = x->esq;
        x->esq = y->dir;

        if(y->dir != NIL){
            y->dir->father = x;
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

    // Rotação a esquerda espelhando a direita kkkkk
    void rotacao_esquerda(rb_no* x){
        rb_no* y = x->dir;
        x->dir = y->esq;

        if(y->esq != NIL){
            y->esq->father = x;
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
    
    // Fix mágico do libro da usp
    void fix_insert(rb_no* no){
        while(no->father->cor == RED){ // vermelho
            //rb_no* tio = no->father->father->esq;
            if(no->father == no->father->father->esq){
                rb_no* tio = no->father->father->dir;
                if(tio->cor == RED){ // tio é vermelho!!!!!!! (Caso 1)
                    no->father->cor = BLACK;
                    tio->cor = BLACK;
                    no->father->father->cor = RED;
                    no = no->father->father;
                }else{
                    if(no == no->father->dir){ // caso2: no é filho direito, roda e vira caso 3
                        no = no->father;
                        rotacao_esquerda(no);
                    }
                    // caso 3: tio preto e no é filho esquerdo
                    no->father->cor = BLACK;
                    no->father->father->cor = RED;
                    rotacao_direita(no->father->father);
                }
            }else{
                // espelhamento dos casos acima (lado direito)
                rb_no* tio = no->father->father->esq;
                if(tio->cor == RED){ // vermelho
                    no->father->cor = BLACK;
                    tio->cor = BLACK;
                    no->father->father->cor = RED;
                    no = no->father->father;
                }else{
                    if(no == no->father->esq){
                        no = no->father;
                        rotacao_direita(no);
                    }
                    no->father->cor = BLACK;
                    no->father->father->cor = RED;
                    rotacao_esquerda(no->father->father);
                }
            }
        }

        root->cor = BLACK;
    }

    // Insert da árvore (tbm só funciona graças ao livro da usp)
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
        if(y == NIL){ // se for o root aqui
            //new_node->cor = false; // faz a raíz ficar preta
            root = new_node;
        }else if(new_node->palavra < y->palavra){
            y->esq = new_node;
        }else{
            y->dir = new_node;
        }

        // PRECISA DISSO AQUI, se n os filhos vão ser NULL msm e vai crashar
        new_node->esq = NIL;
        new_node->dir = NIL;
        new_node->cor = RED;

        // rodar a árvore e fazer pinturas
        fix_insert(new_node);
    }

    // Acha o mínimo de uma sub árvore (só andar pra esquerda pra sempre)
    rb_no* tree_minimum(rb_no* node){
        while(node->esq != NIL){
            node = node->esq;
        }
        cout << "MINIMUM: " << node->palavra << endl;
        return node;
    }

    // trocar dois nós de lugar sem cagar tudo // nenhuma referência a nintendo aqui
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

    // Remove também do livro da usp pq o gpt só atrasou tudo e nos confundiu
    int rb_remove(string palavra){        
        rb_no* z = rb_search(palavra);
        if(z == NIL){ return 1; }

        rb_no* y = z;
        rb_no* x = NIL;
        bool y_original_color = y->cor; // Salva a cor original pra fazer o fix
        
        // primeiro faz um remove normal dos nós, se for RED tá ok
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
        // se n for RED n tá ok, tem q dar o fix
        if(y_original_color == BLACK){
            fix_delete(x);
        }

        // retorna q deu tudo certo
        return 0;
    }

    // Mais um fix mágico da usp(livro)
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
                // mesma coisa soq espelhado
                rb_no* irmao = no->father->esq;

                if(irmao->cor == RED){
                    irmao->cor = BLACK;
                    no->father->cor = RED;
                    rotacao_direita(no->father);
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

    // essa busca aqui ficou bom dms
    rb_no* rb_search(string palavra, rb_no* current){
        if(current == NIL){ return NIL; } // se fosse NULL ia crashar, um caso q o NIL nos salvou
    
        if(current->palavra == palavra){
            return current;
        }else{
            if(current->palavra > palavra){ // Recursividade top 5 melhores práticas
                return rb_search(palavra, current->esq);
            }else{
                return rb_search(palavra, current->dir);
            }
        }
    }
    // Deixar o search mais fácil pra usar lá no main né, tadinho dos devs
    rb_no* rb_search(string palavra){
        return rb_search(palavra, root);
    }

    // o tal do print em ordem alfabética
    void print_emordem(rb_no* no){
        if(no != NIL){
            print_emordem(no->esq);
            cout << (no->cor == RED ? BG_RED : BG_BLACK) << FG_WHITE;
            cout << no->palavra << RESET "   ";
            print_emordem(no->dir);
        }
    }

    // print pre-ordem dentro do arquivo de saida
    void print_arquivo(rb_no* no, ofstream &out){
        if(no != NIL){
            out << (no->cor ? "RED" : "BLK") << "   " << no->palavra << endl;
            out << "      " << no->significado << endl << endl;

            print_arquivo(no->esq, out);
            print_arquivo(no->dir, out);
        }
    }

    // salva no arquivo arvorefinal.txt mesmo se voce nao quiser
    void autosave(){
        ofstream out("arvorefinal.txt");

        out << "--- Árvore depois das operações feitas (pré-ordem) ---\n";
        print_arquivo(root, out);
        out.close();
    }
};

// COISAS DO MENU INTERATIVO
void gotoxy(int x, int y){
    printf("\e[%d;%df", y, x); // posiciona o cursor do print em lugar específico
    fflush(stdout); // é bom pra printar tipo a seta pra cima
}

// O tal do FRONT!!!!!
void print_menu(int x, int y){
    clrscr(); // limpa a tela
    printf(BG_BLACK "===   \t" FG_GREEN "Venilso & Esquilo's" RESET " " BG_RED FG_BLACK "\'Red " BG_BLACK FG_RED " Velvet\'" RESET BG_BLACK" Tree\t     ===\n" RESET);
    printf("   " BG_WHITE FG_BLACK"Adicionar" RESET " \t");
    printf("   " BG_WHITE FG_BLACK"Remover" RESET " \t");
    printf(BG_WHITE FG_BLACK"Imprimir" RESET " \t");
    printf(BG_WHITE FG_BLACK"Busca\n");
    printf(RESET);

    // Aqui coloca a posição certa da seta de seleção
    gotoxy(x, y);
    printf("\u2191\n");
    gotoxy(x, y+1); // Menu informativo dos botões
    printf("Esc - Sair | <- Navegar -> | Enter - Selecionar |\n");
}

struct termios oldt, newt;
 // Começa a captar as teclas noterminal
void initInput(){
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
// Volta o terminal ao normal
void restoreInput(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
// Vai ver qual é a tecla certinha pressionada
int handleInput(){
    char c = 0;
    if(read(STDIN_FILENO, &c, 1) == 0){
        return 0;
    }

    if(c == '\x1B'){
        char seq[2];

        if(read(STDIN_FILENO, &seq[0], 1) == 0){ return 27; } // esc
        if(read(STDIN_FILENO, &seq[1], 1) == 0){ return 27; } // esc

        if(seq[0] == '['){
            switch(seq[1]){
                case 'C':
                    return 1001;
                case 'D':
                    return 1000;
            }
        }

        return 27;
    }

    return c;
}

int main(int argc, char* argv[]){
    rb_tree arvore = rb_tree(); // A árvore principal aqui

    string file_error = "f"; // Vari´´avel pra verificar erro na leitura dos arquivos
    // caso não tenha arquivo nos argumentos ou caso dê merda pra abrir
    if(argc < 2){
        printf(BG_RED "Ocorreu um erro ao encontrar ou abrir o arquivo!\n" RESET);
        printf("Pressione qualquer tecla para seguir com a vida normalmente...\n");
        getline(cin, file_error);
    }
    ifstream in(argv[1]);
    if(!in){
        printf(BG_RED "Ocorreu um erro ao encontrar ou abrir o arquivo!\n" RESET);
        printf("Pressione qualquer tecla para seguir com a vida normalmente...\n");
        getline(cin, file_error);
    }

    if(file_error == "f"){
        // pegando palavras e significados
        string linha;
        while(getline(in, linha)){
            istringstream iss(linha);
            string palavra, significado;

            if(!(iss >> palavra)){
                continue;
            }
            getline(iss, significado);
            if(!significado.empty() && significado.front() == ' '){
                significado.erase(0, 1);
            }

            arvore.rb_insert(palavra, significado);
        }
        
        arvore.autosave();
    }

    // MENU BONITINHO
    bool running = true;
    initInput(); // Começa a consumir as teclas do terminal

    int pos_x = 8, pos_y = 3; // posição inicial da seta
    print_menu(pos_x, pos_y);

    bool select = false; // Usa isso pra quando selecionar uma opção

    while(running){ // Running para quando aperta esc
        
        // HandleInput
        int key = handleInput();
    
        switch(key){
            case 10: // Enter
                // Select
                select = true;
                break;
            case 27: // esc
                running = false;
                break;
            case 1000: // left
                pos_x = pos_x==8 ? 51 : pos_x == 51 ? 37 : pos_x == 23 ? 8 : 23;
                print_menu(pos_x, pos_y);
                break;
            case 1001: // Right
                pos_x = pos_x==51 ? 8 : pos_x == 8 ? 23 : pos_x == 23 ? 37 : 51;
                print_menu(pos_x, pos_y);
                break;
        }

        // Aqyu quando da enter em uma opção
        if(select == true){
            restoreInput(); // restaura o temrinal ao normal pq o usuário vai digitar coisas
            //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // USAR ISSO PRA CONSUMIR \n DEPOIS DO CIN, se n ele vai usar o cin no getline

            // Variáveis usadas dentro do switch
            string temp_palavra;
            string temp_significado;
            rb_no* palavra_buscada;
            int fail; // verifica se deu erro ao achar uma palabra

            clrscr(); // limpa a tela
            gotoxy(1,1);

            switch(pos_x){
                case 8: // Adicionar
                    printf("Palavra a adicionar: ");
                    cin >> temp_palavra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    printf("Significado: ");
                    getline(cin, temp_significado);

                    // Aqui insere de fato
                    arvore.rb_insert(temp_palavra, temp_significado);
                    printf("Palavra inserida com sucesso!\nPressione qualquer tecla para voltar ao menu!\n");
                    getline(cin, temp_palavra);
                    arvore.autosave();
                    
                    // Sai do sub-menu
                    select = false;
                    initInput();
                    print_menu(pos_x, pos_y);
                    break;
                case 23: // Remover
                    printf("Digite a palavra a ser removida: ");
                    cin >> temp_palavra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    fail = arvore.rb_remove(temp_palavra);
                    if(fail){ // se deu erro
                        printf(FG_RED BG_WHITE "PALAVRA NÃO ENCONTRADA\n" RESET);
                        printf("Pressione qualquer tecla para voltar ao menu!\n");
                        getline(cin, temp_palavra);
                    }
                    arvore.autosave();

                    // Sai do sub-menu
                    select = false;
                    initInput();
                    print_menu(pos_x, pos_y);
                    break;
                case 37: // Imprimir
                    printf("--- Árvore Em Ordem ---\n\n");
                    arvore.print_emordem(arvore.root);
                    
                    printf("\n\nPressione qualquer tecla para voltar ao menu!");
                    getline(cin, temp_palavra);

                    // Sai do sub-menu
                    select = false;
                    initInput();
                    print_menu(pos_x, pos_y);
                    break;
                case 51: // Buscar
                    printf("Digite a palavra que você deseja buscar: ");
                    cin >> temp_palavra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    palavra_buscada = arvore.rb_search(temp_palavra);
                    if(palavra_buscada == arvore.NIL){
                        printf("NÃO FOI POSSÍVEL ENCONTRAR SUA PALAVRA\nPressione qualquer tecla para voltar ao menu!");
                        getline(cin, temp_palavra);
                    }else{
                        cout << "Palavra: " << palavra_buscada->palavra << endl;
                        cout << "Significado: " << palavra_buscada->significado << endl;


                        printf("Pressione qualquer tecla para voltar ao menu!");
                        getline(cin, temp_palavra);
                    }

                    // Sai do sub-menu
                    select = false;
                    initInput();
                    print_menu(pos_x, pos_y);
                    break;
            }
        }

    }

    printf("Árvore salva com sucesso em arvorefinal.txt!\n"); // Print final

    restoreInput(); // Arruma o temrinal pro normal
    // ACABOOOUUUU!!!!!!

    return 0;
}
