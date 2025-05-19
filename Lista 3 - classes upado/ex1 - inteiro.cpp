//um grande obrigado ao senhor esquilo e o franck por fazerem tudo

#include <iostream>
using namespace std;

#define MAX_SIZE 40

class InteiroGigante{
    public:
    int iNumero[MAX_SIZE];
    private:
    int iSize;
    
    private:
    void Resize(){
        for(int i = 0; i < MAX_SIZE ; i++){
            if(iNumero[i] != 0){
                this->iSize = MAX_SIZE-i;
                break;
            }
        }
    }
    
    public:
    InteiroGigante(){
        for(int i = 0; i < MAX_SIZE; i++){
            iNumero[i] = 0;
        }
    }
    
    int ReadInteiroGigante(){
        string sEntrada; 
        cin >> sEntrada;
        int iVectorPos = MAX_SIZE - sEntrada.size();
        
        if(sEntrada.size() > MAX_SIZE){
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

    InteiroGigante operator+(InteiroGigante c_B){
        int iCarryIn = 0;
        InteiroGigante c_C;
        
        for(int i = 39; i >= 0; i--){
            if(this->iNumero[i] + c_B.iNumero[i] + iCarryIn < 10){
                c_C.iNumero[i] = this->iNumero[i] + c_B.iNumero[i] + iCarryIn;
                iCarryIn = 0;
            }else{
                c_C.iNumero[i] = (this->iNumero[i] + c_B.iNumero[i] + iCarryIn) - 10;
                iCarryIn = 1;
            }
        }
        
        if(iCarryIn){
            cout << "OVERFLOW" << endl;
        }
        
        c_C.Resize();
        return c_C;
    }

    void operator+=(InteiroGigante c_B){
        InteiroGigante c_C = this->operator+(c_B);
        for(int i = 0; i < 40; i++){
            this->iNumero[i] = c_C.iNumero[i];
        }
    }

    InteiroGigante operator-(InteiroGigante c_Other){
        // TODO: ARRUMAR RESULTADOS NEGATIVOS
        InteiroGigante c_C;
        int *iMaiorNumero, *iMenorNumero;
        if(this->operator>(c_Other)){
            iMaiorNumero = this->iNumero;
            iMenorNumero = c_Other.iNumero;
        }else{
            cout << "OVEFLOW FROM HERE" << endl;
        }


        for(int i = 39; i >= MAX_SIZE-this->iSize; i--){
            if(iMaiorNumero[i] < iMenorNumero[i] && i-1 >= 0){
                iMaiorNumero[i-1] -= 1;
                iMaiorNumero[i] += 10;
            }else if(i-1 < 0){
                cout << "OVERFLOW" << endl;
                break;
            }


            c_C.iNumero[i] = iMaiorNumero[i] - iMenorNumero[i];
        }

        c_C.Resize();
        return c_C;
    }

    // return true if this is bigger than other
    bool operator>(InteiroGigante c_Other){
        for(int i = 0; i < MAX_SIZE; i++){
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
        for(int i = 0; i < MAX_SIZE; i++){
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
        for(int i = 0; i < MAX_SIZE; i++){
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
    meuNumero.PrintInteiroGigante();
    cout << "SIZE : " << meuNumero.GetSize() << endl;
    cout << "------------------------" << endl;
    meuNumero2.ReadInteiroGigante();
    meuNumero2.PrintInteiroGigante();
    cout << "SIZE : " << meuNumero.GetSize() << endl;
    
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
    cout << "------------COMP<==>----------" << endl << endl << endl << endl;

    cout << "------------SOMA------------" << endl;
    InteiroGigante meuNumero3 = meuNumero + meuNumero2;
    //meuNumero += meuNumero2;
    meuNumero3.PrintInteiroGigante();
    cout << "------------SOMA------------" << endl << endl;

    
    cout << "----------SUBTRAÇÃO------------" << endl;
    InteiroGigante meuNumero4 = meuNumero - meuNumero2;
    meuNumero4.PrintInteiroGigante();
    cout << "----------SUBTRAÇÃO------------" << endl << endl;
}