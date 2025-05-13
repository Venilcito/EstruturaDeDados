//um grande obrigado ao senhor esquilo e o franck por fazerem tudo

#include <iostream>
using namespace std;

class InteiroGigante{
    private:
    int iNumero[40];
    int iSize;
    
    private:
    void Resize(){
        for(int i = 0; i < 40 ; i++){
            if(iNumero[i] != 0){
                this->iSize = 40-i;
                break;
            }
        }
    }
    
    public:
    InteiroGigante(){
        for(int i = 0; i < 40; i++){
            iNumero[i] = 0;
        }
    }
    
    int ReadInteiroGigante(){
        string sEntrada; 
        cin >> sEntrada;
        int iVectorPos = 40 - sEntrada.size();
        
        if(sEntrada.size() > 40){
            cout << "Número inválido" << endl;
            return 1;
        }
        
        for(char i : sEntrada){
            iNumero[iVectorPos] = i - '0';
            iVectorPos++;
        }
        
        this->iSize = sEntrada.size();
        
        return 0;
    }
    
    void PrintInteiroGigante(){
        bool bFlag = false;
        for(auto i : iNumero){
            if(i == 0 && !bFlag){
                continue;
            }
            
            bFlag = true;
            cout << i;
        }
        cout << endl;
    }
    
    int operator+(InteiroGigante c_B){
        int iCarryIn = 0;
        
        //InteiroGigante *c_Maior = c_A->iSize > c_B->iSize ? c_A : c_B;
        
        for(int i = 39; i >= 0; i--){
            if(this->iNumero[i] + c_B.iNumero[i] + iCarryIn < 10){
                this->iNumero[i] += c_B.iNumero[i] + iCarryIn;
                iCarryIn = 0;
            }else{
                this->iNumero[i] = (this->iNumero[i] + c_B.iNumero[i] + iCarryIn) - 10;
                iCarryIn = 1;
            }
        }
        
        if(iCarryIn){
            cout << "OVERFLOW" << endl;
            return iCarryIn;
        }
        
        Resize();
        return iCarryIn;
    }
    
    int GetSize(){
        return this->iSize;
    }
    
};

int main(){
    InteiroGigante meuNumero;
    InteiroGigante meuNumero2;
    meuNumero.ReadInteiroGigante();
    cout << "------------------------" << endl;
    meuNumero.PrintInteiroGigante();
    cout << "SIZE : " << meuNumero.GetSize() << endl;
    cout << "------------------------" << endl;
    meuNumero2.ReadInteiroGigante();
    cout << "------------------------" << endl;
    meuNumero2.PrintInteiroGigante();
    cout << "------------SOMA----------" << endl;

    meuNumero + meuNumero2;
    
    meuNumero.PrintInteiroGigante();
    cout << "SIZE : " << meuNumero.GetSize() << endl;
}
