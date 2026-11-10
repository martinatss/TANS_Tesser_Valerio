#include "Cylinder.h"

Cylinder::Cylinder() : TObject(), lenght(0), thickness(0), radius(0), Chi_0(0) {}

Cylinder::Cylinder(double len, double thick, double rad, double chi_0) :TObject(), lenght(len), thickness(thick), radius(rad), Chi_0(chi_0) {}