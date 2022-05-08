#include <iostream>
#include <string>
#include "Regresion.h"
#include <cmath>
using namespace std;

int main(){

    //.i
	string input;
	cout<<"Escriba el archivo: ";
	getline(cin, input);
	if(input.length() == 0){
		cout<<"No se ingreso ningun archivo"<<endl;
		return 0;
	}
    Regresion regresion;
    regresion.readFile(input);
    return 0;
}