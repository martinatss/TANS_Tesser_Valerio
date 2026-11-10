#include "Point.h"

Point::Point() : TObject(), Phi(0), R(0), Z(0) {}

Point::Point(double phi, double r, double z) : TObject(), Phi(phi), R(r), Z(z) {}

 
Point& Point::operator=(Point& P) { //usiamo la keyword "this": lo usiamo come puntatore dell'oggetto, quindi punta all'indirizzo di memoria.  
    TObject::operator=(P);
    R = P.GetR();
    Z = P.GetZ();
    Phi = P.GetPhi();
    return *this;
}