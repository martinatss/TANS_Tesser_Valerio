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
        double GetZ() const {return Z;}

        //costruttori
        Particle();
        Particle(double Phi, double Z, double Eta);
        
        
        void Transport(Cylinder layer); //quello dal vertice alla beam pipe, che prende il punto di inizio in coordinate cartesiane
        //void Transport( ,Cylinder layer12);/quello dalla beam pipe al layer 1 e dal layer 1 al layer 2, che prende il punto di inizio in coordinate cilindriche
        void MultipleScattering()
        bool Interaction(Cylinder layer)
        Point Getvertex()
        void SetVertex(double X_start, double Y_start, double Z_start)


    private:
        double Phi
        double Eta
        double Theta
        double Z

        double X_vert
        double Y_vert
        double Z_vert

        double R_0
        double Theta_0
        double Z_0



};






#endif