#ifndef PARTICLE_H
#define PARTICLE_H

#include "TObject.h" 
#include <cmath>
#include "Point.h"
#include "Cylinder.h"



class Particle: public TObject{
    public: 
        //member function (Get)      
        double GetPhi() const {return Phi;}
        double GetEta() const {return Eta;}
        double GetHitPhi() const { return std::atan2(Y, X);} //ritorna quello della collisione
        double GetZ() const {return Z;}

        //costruttori
        Particle();
        Particle(double eta, double z, double phi);
        
        
        void Transport(const Cylinder& layer); //quello dal vertice alla beam pipe, che prende il punto di inizio in coordinate cartesiane
        //void Transport( ,Cylinder layer12);/quello dalla beam pipe al layer 1 e dal layer 1 al layer 2, che prende il punto di inizio in coordinate cilindriche
        void MultipleScattering(const Cylinder& layer, double beta, double momentum);
        bool Interaction(const Cylinder& layer) const;
        void SetVertex(double X_start, double Y_start, double Z_start);
        void SetAngles(double eta, double phi);


    private:
        double Phi;
        double Eta;
        double Theta;
        double Z;

        double X;
        double Y;
        

        

        


};






#endif