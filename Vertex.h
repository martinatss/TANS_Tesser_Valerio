//non serve perché tanto definiamo un trasport con x y z in coord cartesiane e basta

#ifndef VERTEX_H
#define VERTEX_H

#include "TObject.h" // con le virgolette perché non sono della standard library creata da root
#include <cmath>

class Vertex: public TObject{
    public:
        double GetX_vert() const {return X_vert;}
        double GetY_vert() const {return Y_vert;}
        double GetZ_vert() const {return Z_vert;}

        void
        
    private:
        double X_vert;
        double Y_vert;
        double Z_vert;


};

#endif