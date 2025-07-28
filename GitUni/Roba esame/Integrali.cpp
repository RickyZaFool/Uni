#include <iostream>
#include <cmath>
#include <TRandom3.h>
#include <TMath.h>
using namespace std;

bool isInShape(double x, double y, double r){
    bool inShape = false;
    if(x*x + y*y <= r*r ){
        inShape = true;
    }
    return inShape;
}

bool isInHyperSphere(double x, double y, double z, double t, double r){
    bool inSphere = false;
    if(x*x + y*y + z*z + t*t <= r*r){
        inSphere = true;
    }
    return inSphere;
}

int main(){
    TRandom3 rnd;
    //In sequence: we want to calculate the 2D integral of a shape, the hypervolume of a 4D sphere.

    //Let's suppose we have the shape and the sphere defined elsewhere.
    int steps = 1000000;
    double radius = 1;
    int inShape = 0;
    int inSphere = 0;
    for(int i = 0; i < steps; i++){
    
	    double x = radius*(rnd.Rndm()*2-1);
	    double y = radius*(rnd.Rndm()*2-1);
        if(isInShape(x,y,radius)){
            inShape++;
        }
	    double z = radius*(rnd.Rndm()*2-1);
	    double t = radius*(rnd.Rndm()*2-1);

        if(isInHyperSphere(x,y,z,t,radius)){
            inSphere++;
        }

    }

    //the actual hypersphere volume is
    double vol = pow(radius, 4) * pow(3.1415, 2) / (TMath::Gamma(3));


    cout << "Area of the circle is approximately " << double(inShape) * 4 * radius / steps  << " compared to the actual area which is " << 3.1415 * radius * radius  << endl;
    cout << "Volume of the hypersphere is approximately " << double(inSphere) * pow(2 * radius , 4) / steps << " compared to the actual volume which is " << vol << endl;

}