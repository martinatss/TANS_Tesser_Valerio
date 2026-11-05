#include "Cylinder.h"

Cylinder::Cylinder() : TObject(), lenght(0), thickness(0), radius(0), RadiationLenght(0) {}

Cylinder::Cylinder(double len, double thick, double rad, double chi_0) :TObject(), lenght(len), thickness(thick), radius(rad), RadiationLenght(chi_0) {}


Cylinder::Cylinder( double thickness, double radius, double Chi_0): TObject(), lenght(0), thickness(thickness), radius(radius), RadiationLenght(Chi_0) {}