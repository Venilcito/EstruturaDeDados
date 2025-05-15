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
    
    //=================================
    //===========OPERATORS=============
    //=================================

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

    int operator-(InteiroGigante c_Other){
        // TODO: ARRUMAR RESULTADOS NEGATIVOS

        int *iMaiorNumero, *iMenorNumero;
        bool bNegative = false;
        if(this->operator>(c_Other)){
            iMaiorNumero = this->iNumero;
            iMenorNumero = c_Other.iNumero;
        }else{
            iMaiorNumero = c_Other.iNumero;
            iMenorNumero = this->iNumero;
            bNegative = true;
        }


        for(int i = 39; i >= 0; i--){
            if(iMaiorNumero[i] < iMenorNumero[i] && i-1 >= 0){
                iMaiorNumero[i-1] -= 1;
                iMaiorNumero[i] += 10;
                
                cout << "1: " << iMaiorNumero[i] << " - 2: " << iMenorNumero[i] << " = " << iMaiorNumero[i] - iMenorNumero[i] << endl;
            }else if(i-1 < 0){
                // OVERFLOW
            }

            iMaiorNumero[i] = iMaiorNumero[i] - iMenorNumero[i];
        }

        Resize();
        return 0;
    }

    // return true if this is bigger than other
    bool operator>(InteiroGigante c_Other){
        for(int i = 0; i < 40; i++){
            if(iNumero[i] > c_Other.iNumero[i]){
                return true;
            }else if(iNumero[i] < c_Other.iNumero[i]){
                return false;
            }
        }

        return false;
    }

    // return true if this is less than other
    bool operator<(InteiroGigante c_Other){
        for(int i = 0; i < 40; i++){
            if(iNumero[i] < c_Other.iNumero[i]){
                return true;
            }else if(iNumero[i] > c_Other.iNumero[i]){
                return false;
            }
        }
        return false;
    }

    // return true if both are equal
    bool operator==(InteiroGigante c_Other){
        for(int i = 0; i < 40; i++){
            if(this->iNumero[i] != c_Other.iNumero[i]){
                return false;
            }
        }
        return true;
    }

    // return true if them are not equal
    bool operator!=(InteiroGigante c_Other){
        return !(this->operator==(c_Other));
    }

    // return true if this is bigger or equal than other
    bool operator>=(InteiroGigante c_Other){
        return (this->operator>(c_Other) || this->operator==(c_Other));
    }

    // return true if this is less or equal than other
    bool operator<=(InteiroGigante c_Other){
        return (this->operator<(c_Other) || this->operator==(c_Other));
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
    
    cout << "------------COMP<==>----------" << endl;
    if(meuNumero > meuNumero2){
        cout << "num1 é maior que 2" << endl;
    }else if(meuNumero < meuNumero2){
        cout << "num1 é menor que 2" << endl;
    }
    if(meuNumero >= meuNumero2){
        cout << "num1 é maior ou igual a 2" << endl;
    }else if(meuNumero <= meuNumero2){
        cout << "num1 é menor ou igual a 2" << endl;
    }
    if(meuNumero == meuNumero2){
        cout << "num1 é igual a 2" << endl;
    }else if(meuNumero != meuNumero2){
        cout << "num1 é diferente de 2" << endl;
    }

    cout << "------------SOMA------------" << endl;
    //meuNumero + meuNumero2;
    //meuNumero.PrintInteiroGigante();
    cout << "----------SUBTRAÇÃO------------" << endl;
    meuNumero - meuNumero2;
    meuNumero.PrintInteiroGigante();
}
