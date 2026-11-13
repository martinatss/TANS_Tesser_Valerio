#ifndef POINT_H //istruzioni di precompilazione: if not defined -> define -> end if
#define POINT_H


class Point: public TObject{ //qui diciamo che Point è figlio di TObject (public perché è difficile ereditare cose private)
    public:
        double GetPhi() const {return Phi;} //per funzioni semplici che stanno in una riga si può scrivere nell'header file .h direttamente "cosa fa" invece di metterlo nel .c
        double GetR() const {return R;}
        double GetZ() const {return Z;}
        double GetX() const {return R*std::cos(Phi);}
        double GetY() const {return R*std::sin(Phi);}
        double GetPhi() const {return Phi;}

        // facciamo le funzioni Set che sono quelle che modificano: chiaramete lo faccio solo delle variabili nel private perchè le altre invece vengono fuori dal codice, non sono dati che gli do io
        void SetPhi(double phi) {Phi = phi;} //metto void perché questa funzione chiaramente non restituisce niente
        void SetR(double r) {R = r;}
        void SetZ(double z) {Z = z;}

        //facciamo i costruttori
        Point();
        Point(double Phi, double R, double Z); //qui potevo dargli anche altri nomi perché non sa che mi riferisco alle variabili definite nel private

        //"operator=" è un operatore che ci permette di definire l'operazione di uguaglinza che in questo caso è una copia
        Point& operator=(Point& P) //P è quello che usiamo come oggetto da copiare. è sempre un punto (perché gli abiamo detto che appartiene alla classe Point)

    private: 
        double Phi;
        double R;
        double Z;

}; 

#endif 