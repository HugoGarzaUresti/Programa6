/*
Hugo Garza A01177091
7/4/2022
El archivo Simpson.h es donde esta la logica de los calculos de la regla de integracion Simpson
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Simpson{
    private:
    long double x;
    long double dof;
    long double p;
    int segments;
    long double W;
    long double error;
    public:
    Simpson();
    Simpson(double, double);
    long double tDistribution(double);
    long double gammaFunction(long double);
    long double sumOfF(int);
    long double pCalculation();
};

Simpson::Simpson(){

}

Simpson::Simpson(double X, double DOF){
    x = X;
    dof = DOF;
    segments = 100;
    error = 0.00000000001;
    W = x/segments;
};
/*
Funcion gammaFunction: Hace el calculo de la funcion gamma en caso de ser numero entero o con decimales
Parametros: Numero double a usar en el calculo
Regresa: double con el valor de la funcion en ese punto de la curva
*/
//.i
long double Simpson::gammaFunction(long double num){
    if(fmod(num,1) == 0){
        long double n = num - 1;
        long double ans = 1;
        for(int i = 1; i <= n; i++){
            ans = ans * i;
        }
        return ans;
    }else{
        long double n = num - 1;
        long double ans = 1;
        for(double i = n; i > 0; i--){
            if (i == 0.5) {
                ans = ans * sqrt(M_PI) * i;
            }else{
                ans = ans * i;
            }
        }
        return ans;
    }
}
/*
Funcion tDistribution: Hace el calculo de la distribucion T usando la funcion gamma y algunas funciones de cmath
Parametros: valor de x
Regresa: double con el valor de la distribucion
*/
//.i
long double Simpson::tDistribution(double x){
    long double numerator = gammaFunction((dof + 1)/2);
    long double denominator = (sqrt(dof * M_PI)) * gammaFunction(dof/2);
    long double ans = (numerator / denominator) * pow(1 + (pow(x,2) / dof), -1 * (dof + 1) / 2);
    return ans;
}
/*
Funcion sumOfF: Hace el calculo de la sumatoria de la distribucion t en pares e impares
Parametros: num de segmentos
Regresa: la suma de ambas sumatorias con su multiplicador
*/
//.i
long double Simpson::sumOfF(int seg){
    long double sum1 = 0;
    long double sum2 = 0;
    for(int i = 1; i<=seg-1; i++){
        if(i % 2 != 0){
            sum1 = sum1 + tDistribution(W * i);
        }
    }
    for(int i = 1; i<=seg-2; i++){
        if(i % 2 == 0){
            sum2 = sum2 + tDistribution(W * i);
        }
    }
    return ((4 * sum1) + 2 * sum2);
}
/*
Funcion pCalculation: Hace el calculo Simpson usando la ditribucion t y la funcion gamma
Parametros: Ninguno
Regresa: La aproximacio con 5 decimales de precision y error menor a 0.0000001
*/
//.i
long double Simpson::pCalculation(){
    long double newResult = 1;
    long double oldResult = 100;
    while(oldResult - newResult > error){
        oldResult = (W / 3) * (tDistribution(0) + sumOfF(segments) + tDistribution(x));
        newResult =  (W / 3) * (tDistribution(0) + sumOfF(segments * 2) + tDistribution(x));
        segments = segments * 2;
    }
    return oldResult;
}





