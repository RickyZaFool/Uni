#include <iostream>
#include <cmath>
using namespace std;

//Ricerca degli zeri e di massimi e minimi di una funzione

//Prima di tutto, la funzione di cui vogliamo trovare massimi minimi e zeri
double f(double x){
    double y = pow(x,3)-8*pow(x,2)+4*x+5;  //cambiare y a seconda della funzione ovviamente
    return y;
}

double extreme(double a, double b, double precision, bool isMinimum){
    if(a > b){
        double tmp = a;
        a = b;
        b = tmp;
    }
    double GR = 1.61803398875; //Golden Ratio
    double c = b + (a - b) / GR;
    double d = a + (b - a) / GR;
    while(b - a > precision){
        if(isMinimum){
            if(f(c) < f(d)){
                b = d;
                d = c;
                c = b + (a - b) / GR;
            }
            else{
                a = c;
                c = d;
                d = a + (b - a) / GR;
            }
        }
        else{
            if(f(c) > f(d)){
                b = d;
                d = c;
                c = b + (a - b) / GR;
            }
            else{
                a = c;
                c = d;
                d = a + (b - a) / GR;
            }
        }
    }
    return (a + b) / 2;
}


int main(){
    
    //Ricerca di uno zero dati due punti di partenza.
    double precision = 0.0000001;
    double x1 = -10;
    double a = x1;
    double x2 = 10;
    double b = x2;
    double xmed =  -100;
    while(abs(x1 - x2) > precision){
        if(f(x1) * f(x2) > 0){
            cout << "the value at the extremes has the same sign" << endl;
            break;
        }

        xmed = (x1 + x2) / 2;
        if(f(xmed) == 0){
            break;
        }

        if(f(xmed) * f(x1) < 0){
            x2 = xmed;
        }else{x1 = xmed;}
    }

    if(xmed == -100){
        cout << "there has been some error" << endl;
    }else{cout << "the zero found between the two extremes " << a << " and " << b << " is at " << xmed << " with a precision of " << precision << ". Note that f(x) evaluates " << f(xmed) << " at that point" << endl;}
     
    
    //Ricerca di un estremo della funzione dati due punti di partenza
    bool isMinimum = false;
    
    cout << "the extreme found between " << a << " and " << b << " is " << extreme(a, b, precision, isMinimum) << endl;
    
    return 0;
}