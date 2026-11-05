#include "Particle.h"
#include "TRandom3.h"

Particle::Particle() : TObject(), Eta(0), Z(0), Phi(0), Theta(0), X(0), Y(0) {}
Particle::Particle(double eta, double z, double phi) : TObject(), Eta(eta), Z(z), Phi(phi), X(0), Y(0)  {
    Theta =  2.0 * std::atan(std::exp(-Eta));
}
void Particle::SetAngles(double eta, double phi){
    Eta = eta;
    Phi = phi;
    Theta = 2.0 * std::atan(std::exp(-Eta));
}
void Particle::Transport(const Cylinder& layer) {
    
    double c1 = std::sin(Theta)*std::cos(Phi);
    double c2 = std::sin(Theta)*std::sin(Phi);
    double c3 = std::cos(Theta);
    
    double SqrtDelta = std::sqrt((X*c1 + Y*c2)*(X*c1 + Y*c2) - (c1*c1+c2*c2)*(X*X+Y*Y - layer.Getradius()*layer.Getradius()));
    double t = (-(X*c1 + Y*c2) + SqrtDelta)/(c1*c1 + c2*c2);
    X = X +c1*t;
    Y = Y + c2*t;
    Z = Z + c3*t;
}

bool Particle::Interaction(const Cylinder& layer) const{
    //il controllo è veloce in quanto si è già trasportato
    if((Z >= -layer.Getlenght()/2) && (Z <= layer.Getlenght()/2)){
        return true;
    }
    else {return false;}

}

void Particle::MultipleScattering(const Cylinder& layer, double beta, double momentum){
    int z = 1; //charge = e
    double PathOverRad = layer.Getthickness()/std::sin(Theta)/layer.GetRadiationLenght();
    double ThetaRms = std::sqrt(2)*13.6/(beta*momentum)*z*std::sqrt(PathOverRad)*(1+0.038*std::log(PathOverRad)); // Momentum: in MeV (pc)
    double ThetaScatter = gRandom->Gaus(0, ThetaRms);
    double PhiScatter = gRandom->Uniform(0, 2*M_PI);

    //si ruota la matrice per ottenere il nuovo angolo

    double RM[3][3];  //RM = RotationalMatrix
    RM[0][0]= -1.0*std::sin(Phi);
    RM[1][0]= std::cos(Phi);
    RM[2][0]= 0;
    RM[0][1]= -1.0*std::cos(Phi)*std::cos(Theta);
    RM[1][1] = -1.0*std::sin(Phi)*std::cos(Theta);
    RM[2][1] = std::sin(Theta);
    RM[0][2] = std::sin(Theta)*std::cos(Phi);
    RM[1][2] = std::sin(Theta)*std::sin(Phi);
    RM[2][2] = std::cos(Theta);

    double cdp[3]; 
    double cd[3];

    cdp[0]=std::sin(ThetaScatter)*std::cos(PhiScatter);
    cdp[1]=std::sin(ThetaScatter)*std::sin(PhiScatter);
    cdp[2]=std::cos(ThetaScatter);
    
    //cd = RM*cdp

    for(int i = 0; i<3; i++){
        cd[i]=0;
        for(int j = 0; j<3; j++){
            cd[i]= cd[i]+RM[i][j]*cdp[j];
        }
    }
    //tan(phi) = cd[1]/cd[0], cos(phi) = cd[2]
    Theta = std::acos(cd[2]);
    Phi = std::atan2(cd[1], cd[0]);
    Eta = -std::log(std::tan(Theta / 2.0));
}

void Particle::SetVertex(double X_start, double Y_start, double Z_start) {
    X= X_start;
    Y = Y_start;
    Z = Z_start;
}