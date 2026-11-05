#include "Point.h"

Point::Point() : TObject(), Phi(0), R(0), Z(0) {}

Point::Point(double phi, double r, double z) : TObject(), Phi(phi), R(r), Z(z) {}

 
/*Point& Point::operator=( const Point& P) { //usiamo la keyword "this": lo usiamo come puntatore dell'oggetto, quindi punta all'indirizzo di memoria.  
    TObject::operator=(P); 
    R = P.GetR();
    Z = P.GetZ();
    Phi = P.GetPhi();
    return *this;
}
Point::Point(const Point& P) : TObject(P){
    Phi = P.GetPhi();
    R = P.GetR();
    Z = P.GetZ();
}*/
void Point::SmearingPhi(double RPhiErr){ 
    Phi = Phi + gRandom->Gaus(0., RPhiErr) / R;
    if (Phi > M_PI){
        Phi -= 2. * M_PI;
    }

    if (Phi < -M_PI){
        Phi += 2. * M_PI;
    }
}

ClassImp(Point)  