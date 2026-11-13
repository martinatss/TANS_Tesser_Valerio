#include "Particle.h"

Particle::Particle() : TObject(), Eta(0), Z(0), Phi(0) {}
Particle::Particle(double eta, double z, double phi) : TObject(), Eta(eta), Z(z), Phi(phi) {
    Theta =  2.0 * atan(exp(-Eta));
}

void Particle::Transport(Cylinder layer) {
    
    double c1 = std::sin(Theta)*std::cos(Phi);
    double c2 = std::sin(Theta)*std::sin(Phi);
    double c3 = std::cos(Theta);
    
    double SqrtDelta = std::sqrt((X_start*c1 + Y_start*c2)*(X_start*c1 + Y_start*c2) - (c1*c1+c2*c2)*(fX0*fX0+fY0*fY0 - layer.Getradius()*layer.Getradius()));
    double t = (-(X_start*c1 + Y_start*c2) + SqrtDelta)/(c1*c1 + c2*c2);
    X_vert = X_vert +c1*t;
    Y_vert = Y_vert + c2*t;
    Z_vert = Z_vert + c3*t;
}

bool Particle::Interaction(Cylinder layer){
    double c1 = std::sin(Theta)*std::cos(Phi);
    double c2 = std::sin(Theta)*std::sin(Phi);
    double c3 = std::cos(Theta);
    
    double SqrtDelta = std::sqrt((X_start*c1 + Y_start*c2)*(X_start*c1 + Y_start*c2) - (c1*c1+c2*c2)*(X_start*X_start+Y_start*Y_start - layer.Getradius()*layer.Getradius()));
    double t = (-(X_start*c1 + Y_start*c2) + SqrtDelta)/(c1*c1 + c2*c2);
    if((Z_vert+c3*t >= -layer.Getradius()/2) && (Z_vert+c3*t <= layer.Getradius()/2)){
        return=True;
    }
    else {return=False;}

}

