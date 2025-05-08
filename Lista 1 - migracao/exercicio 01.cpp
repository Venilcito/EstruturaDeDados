#include <iostream>
using namespace std;

int main(){
    
    float celsius;
    cout << "Digite uma temperatura em C: ";
    cin >> celsius;

    float fahrenheit = celsius * 1.8 + 32;

    if(fahrenheit < 0){
        cout << "Temperatura abaixo de zero: " << fahrenheit << " F";
    } else{
        cout << "Temperatura: " << fahrenheit << " F";
    }

    return 0;
}