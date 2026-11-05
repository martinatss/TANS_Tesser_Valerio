#ifndef CYLINDER_H
#define CYLINDER_H

#include "TObject.h"

class Cylinder: public TObject{
    public:
        double Getlenght() const {return lenght;}
        double Getthickness() const {return thickness;}
        double Getradius() const {return radius;}
        double GetRadiationLenght() const {return RadiationLenght;}

        void Setlenght(double len) {lenght = len;}
        void Setthickness(double thick) {thickness = thick;}
        void Setradius(double rad) {radius= rad;}
        void SetRadiationLenght(double chi_0) {RadiationLenght = chi_0;}

        Cylinder();
        Cylinder(double lenght, double thickness, double radius, double Chi_0);
        Cylinder( double thickness, double radius, double Chi_0); 
        //fatto per la BeamPipe: non ha una lunghezza definitiva quindi si mette a 0 (non serve)


    private:
        double lenght;
        double thickness;
        double radius;
        double RadiationLenght;

};



#endif