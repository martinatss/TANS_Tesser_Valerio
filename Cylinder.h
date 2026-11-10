#ifndef CYLINDER_H
#define CYLINDER_H

#include "T.Object"

class Cylinder: public TObject{
    public:
        double Getlenght() const {return lenght;}
        double Getthickness() const {return thickness;}
        double Getradius() const {return radius;}
        double GetChi_0() const {return Chi_0;}

        void Setlenght(double len) {lenght = len}
        void Setthickness(double thick) {thickness = thick;}
        void Setradius(double rad) {radius= rad;}
        void SetChi_0(double chi_0) {Chi_0 = chi_0;}

        Cylinder();
        Cylinder(double lenght, double thickness, double radius, double Chi_0);


    private:
        double lenght
        double thickness;
        double radius;
        double Chi_0;

};



#endif