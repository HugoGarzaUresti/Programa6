/*
Hugo Garza A01177091
3/31/2022
El archivo Regresion.h se encarga de los calculos matematicos asi como del output del programa
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Simpson.h"
#include "DistribucionT.h"
using namespace std;
//.b=105
class Regresion{
    private:
    int x;
    int N;
    double r;
    double r2;
    double b0;
    double b1;
    double yk;
    string line;
    vector<pair<double,double>> data;

    public:
    Regresion();
    vector<pair<double,double>> readFile(string);
    double sumOfX();
    double sumOfY();
    double productOfXY();
    double squaredX();
    double squaredY();
    double rCalculation();
    double averageX();
    double averageY();
    double b0Calculation();
    double b1Calculation();
    double ykCalculation();

};

Regresion::Regresion(){
    int x = 0;
    int N = 0;
    double r = 0;
    double r2 = 0;
    double b0 = 0;
    double b1 = 0;
    double yk = 0;
}

//.i
/*
El metodo readFile abre el archivo dado e introduce los pares de numeros en un vector de pares
Los parametros que recibe son: string el cual es nombre del archivo
Regresa el mismo vector de pares lleno
*/
vector<pair<double,double>> Regresion::readFile(string file){
    ifstream read(file);
    int count = 0;

    while(getline(read,line)){
        string strNum1 = "reset";
        string strNum2 = "reset";
        if(count == 0){
            x = stoi(line);
        }else{
            for(int i = 0; i<line.find(","); i++){
                strNum1[i] = line[i];
            }
            for(int i = line.find(",")+1, j = 0; i<line.length(); i++,j++){
                strNum2[j] = line[i];
            }
            data.push_back(make_pair(stod(strNum1), stod(strNum2)));
        }
        count++;
    }
    N = count - 1;
    
    cout<<"N = "<<N<<endl;
    cout<<"xk = "<<fixed<<setprecision(5)<<x<<endl;
    cout<<"r = "<<fixed<<setprecision(5)<<rCalculation()<<endl;
    cout<<"r2 = "<<fixed<<setprecision(5)<<rCalculation() * rCalculation()<<endl;
    cout<<"b0 = "<<fixed<<setprecision(5)<<b0Calculation()<<endl;
    cout<<"b1 = "<<fixed<<setprecision(5)<<b1Calculation()<<endl;
    cout<<"yk = "<<fixed<<setprecision(5)<<ykCalculation()<<endl;
    double num = 0;
    double den = 0;
    num = (abs(rCalculation()) * (sqrt(N-2)));
    den = sqrt(1-(rCalculation() * rCalculation()));
    double xa = num/den;
    Simpson simpson(xa, N-2);
    double area = 1 - 2*simpson.pCalculation();
    cout<<"sig = "<<fixed<<setprecision(10)<<area<<endl;
    
    return data;
}

//.i
/*
El metodo sumOfX calcula la sumatoria de los valores de X o en otras palabras vector[i].first
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con la suma
*/
double Regresion::sumOfX(){
    double sum = 0;
    for(int i = 0; i<data.size(); i++){
        sum = sum + data[i].first;
    }
    return sum;
}

//.i
/*
El metodo sumOfY calcula la sumatoria de los valores de Y o en otras palabras vector[i].second
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con la suma
*/
double Regresion::sumOfY(){
    double sum = 0;
    for(int i = 0; i<data.size(); i++){
        sum = sum + data[i].second;
    }
    return sum;
}

//.i
/*
El metodo productOfXY calcula la sumatoria del producto de X y Y
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con la suma
*/
double Regresion::productOfXY(){
    double product = 0;
    for(int i = 0; i<data.size(); i++){
        product = product + (data[i].first * data[i].second);
    }
    return product;
}

//.i
/*
El metodo squared calcula la sumatoria del cuadrado de X
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con la suma
*/
double Regresion::squaredX(){
    double sum = 0;
    for(int i = 0; i<data.size(); i++){
        sum = sum + (data[i].first * data[i].first);
    }
    return sum;
}

//.i
/*
El metodo sumOfX calcula la sumatoria del cuadrado de Y
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con la suma
*/
double Regresion::squaredY(){
    double sum = 0;
    for(int i = 0; i<data.size(); i++){
        sum = sum + (data[i].second * data[i].second);
    }
    return sum;
}

//.i
/*
El metodo sumOfX calcula el promedio de X
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el promedio
*/
double Regresion::averageX(){
    return (sumOfX()/N);
}

//.i
/*
El metodo sumOfX calcula el promedio de Y
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el promedio
*/
double Regresion::averageY(){
    return (sumOfY()/N);
}

//.i
/*
El metodo rCalculation calcula la correlacion r con su formula
Los parametros que recibe son: vector de pares data el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el resultado
*/
double Regresion::rCalculation(){
    double numerator = (N * productOfXY()) - (sumOfX() * sumOfY());
    double denominator = sqrt((N*squaredX() - (sumOfX() * sumOfX())) * (N*squaredY() - (sumOfY() * sumOfY())));
    return (numerator/denominator);
}

//.i
/*
El metodo b0Calculation calcula el parametro de regresio b0 con su formula
Los parametros que recibe son: vector de pares  el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el resultado
*/
double Regresion::b0Calculation(){
    return (averageY() - (b1Calculation() * averageX()));
}

//.i
/*
El metodo b1Calculation calcula el parametro de regresio b1 con su formula
Los parametros que recibe son: vector de pares  el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el resultado
*/
double Regresion::b1Calculation(){
    double numerator = (productOfXY()) - (N * averageX() * averageY());
    double denominator = (squaredX() - (N * averageX() * averageX()));
    return (numerator/denominator);
}

//.i
/*
El metodo ykCalculation calcula el valor de Y con su formula
Los parametros que recibe son: vector de pares  el cual contiene los pares de numero X y Y
Regresa un numero tipo doble con el resultado
*/
double Regresion::ykCalculation(){
    return (b0Calculation() + (b1Calculation() * x));
}