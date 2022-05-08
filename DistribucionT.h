/*Hugo Garza A01177091
23/4/2022
El archivo DistribucionT.h es donde esta la parte logica de la integracion de 0 a x de la funcion t
usando Simpson.h para calcular los estimados de p y acercarse a la p dada con error menor a 0.0000001*/
#include <iostream>
#include <cmath>
using namespace std;

class DistribucionT{
    private:
    float p;
    float dof;
    float x;
    float delta;
    float error;
    public:
    DistribucionT(float,float);
    float simpsonIntegral();
    float xCalculation();
};

DistribucionT::DistribucionT(float P, float DOF){
    p = P;
    dof = DOF;
}
/*Funcion xCalculation: Hace el calculo de x0 usando aproximaciones con el metodo simpson con una x inicial de 1
Parametros: Ninguno
Regresa: float con el valor calculado de x0 con error menor a 0.000000001*/
//.i
float DistribucionT::xCalculation(){
    x = 1;
    delta = x/2;
    int count = 0;
    error = 0.0000000001;
    float newResult = 1;
    float oldResult = 100;
    while(abs(newResult - oldResult) > error){
        if(count > 2000){
            return x;
        }
        oldResult = simpsonIntegral();
        if(oldResult < p){
            x = x + delta;
        }else{
            x = x - delta;
        }
        newResult = simpsonIntegral();
          if((oldResult < p && newResult > p) || (oldResult > p && newResult < p) && count != 0){
            delta = delta/2;
        }
        count++; 
    }
    return x;
}
/*Funcion simpsonIntegral: Se manda a llamar la el calculo de p de la clase Simpson.h
Parametros: Ninguno
Regresa: float con el calculo de p dado los valores de x y dof*/
//.i
float DistribucionT::simpsonIntegral(){
    Simpson simpson(x, dof);
    return simpson.pCalculation();
}