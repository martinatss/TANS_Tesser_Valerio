#include "Point.h"
#include "Particle.h"
#include "Cylinder.h"
#include <iostream>
#include "TTree.h"
#include "TRandom3.h"
#include "Config.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TStopwatch.h"

void Simulation(){

    TStopwatch timer;
    timer.Start(); 

    //Loading delle impostazioni e del seed
    Config cfg = LoadSettings("/config/config.cfg");
    gRandom->SetSeed(cfg.Seed);

    //Loading del TFile con le molteplicità e rapidità e relativi histo
    TFile *AssignedDist = TFile::Open("kinem.root", "READ");
    if(!AssignedDist || AssignedDist->IsZombie() || !AssignedDist->IsOpen()){
        std::cerr<<"File delle distribuzioni non trovato e/o corrotto!";
        return;
    }
    TH1F* h_molt = nullptr;
    TH1F* h_rap = nullptr;
    h_rap = (TH1F*)AssignedDist->Get("heta2");
    h_molt = (TH1F*)AssignedDist->Get("hm");
    if(!h_molt){
        std::cerr<<"Impossibile aprire l'istogramma con le molteplicità delle particelle!";
        return;
    }
    if(!h_rap){
        std::cerr<<"Impossibile aprire l'istogramma con la pseudorapidita' delle particelle!";
        return;
    }

    //Creazione file di output
    TFile hfile("simulation_output.root","RECREATE");
    TTree *tree = new TTree("tree", "Oputput tree of simulation");

    TClonesArray *HitsDec1 = new TClonesArray("Point", 10);
    

    TClonesArray *HitsDec2 = new TClonesArray("Point", 10);
    

    TClonesArray *HitsVertex = new TClonesArray("Point", 10);
    

    tree->Branch("Hits1", &HitsDec1);
    tree->Branch("Hits2", &HitsDec2);
    tree->Branch("Vertici", &HitsVertex);

    //Creazione di Beam Pipe e dei 2 rivelatori
    Cylinder BeamPipe = Cylinder(cfg.BeamPipeThickness, cfg.BeamPipeRadius, cfg.BeamPipeRadiationLenght);
    Cylinder FirstDetector = Cylinder(cfg.Detector1Lenght, cfg.Detector1Thickness, cfg.Detector1Radius, cfg.Detector1RadiationLenght);
    Cylinder SecondDetector = Cylinder(cfg.Detector2Lenght, 0, cfg.Detector2Radius, cfg.Detector1RadiationLenght); 

    //creazione dei punti:
    Particle particella = Particle();
    Point p1 = Point();
    Point p2 = Point();

    //avvio simulazione 
    for(int i = 0; i<cfg.NumberOfEvents; i++){
        if (i%5000 == 0)   std::cout << "Simulating vertex n. " << i << std::endl;

        int multiplicity = 0;
        if(cfg.SelectMolteplicity){
            multiplicity = std::round(h_molt->GetRandom());
        }
        else{
            multiplicity = static_cast<int>(gRandom->Uniform(1,cfg.MaxUniformMolteplicity+1));
        }
        
        double x_vtx = gRandom->Gaus(0, cfg.CollisionXRms);
        double y_vtx = gRandom->Gaus(0, cfg.CollisionYRms);
        double z_vtx = gRandom->Gaus(0, cfg.CollisionZRms);

        int NumberOfVertex = 0;
        int NumberOfHits1 = 0;
        int NumberOfHits2 = 0;
        new((*HitsVertex)[NumberOfVertex]) Point(std::atan2(y_vtx, x_vtx), std::sqrt(x_vtx*x_vtx+y_vtx*y_vtx), z_vtx);
            NumberOfVertex++;
        for(int j = 0; j < multiplicity; j++){
            
            double Eta;
            double Phi = gRandom->Uniform(-M_PI, +M_PI);

            particella.SetVertex(x_vtx, y_vtx, z_vtx);
            

            if(cfg.SelectPseudoRapidity){
                Eta = h_rap->GetRandom();
            }
            else{
                Eta = gRandom->Uniform(-2, +2);
            }
            particella.SetAngles(Eta, Phi);

            particella.Transport(BeamPipe);
            if(cfg.MultipleScattering){
                particella.MultipleScattering(BeamPipe, 1, cfg.ParticleMomentum);
            }

            particella.Transport(FirstDetector);
            if(particella.Interaction(FirstDetector)){
                if(cfg.MultipleScattering){
                    particella.MultipleScattering(FirstDetector, 1, cfg.ParticleMomentum);
                }
                //save hit
                p1.SetPhi(particella.GetHitPhi());
                p1.SetZ(particella.GetZ());
                p1.SetR(cfg.Detector1Radius);

                //smearing 
                p1.SmearingPhi(cfg.ArcSmearing);
                p1.SmearingZ(cfg.ZSmearing);
                new((*HitsDec1)[NumberOfHits1]) Point(p1);
                NumberOfHits1++;
            }
            particella.Transport(SecondDetector);
            if(particella.Interaction(SecondDetector)){
                
                //save hit
                p2.SetPhi(particella.GetHitPhi());
                p2.SetZ(particella.GetZ());
                p2.SetR(cfg.Detector2Radius);

                //smearing 
                p2.SmearingPhi(cfg.ArcSmearing);
                p2.SmearingZ(cfg.ZSmearing);
                new((*HitsDec2)[NumberOfHits2]) Point(p2);
                NumberOfHits2++;
            }
            
        }
        //add noise to the detectors
            
            int NoiseOnFirstDec = gRandom->Poisson(cfg.LevelOfNoise);
            for(int k = 0; k<NoiseOnFirstDec; k++){
                new((*HitsDec1)[NumberOfHits1]) Point(gRandom->Uniform(-M_PI, +M_PI), 
                                                        cfg.Detector1Radius, 
                                                        gRandom->Uniform(-cfg.Detector1Lenght/2.,cfg.Detector1Lenght/2.));
                NumberOfHits1++;
            }

            int NoiseOnSecondDec = gRandom->Poisson(cfg.LevelOfNoise);
            for(int k = 0; k<NoiseOnSecondDec; k++){
                new((*HitsDec2)[NumberOfHits2]) Point(gRandom->Uniform(-M_PI, +M_PI), 
                                                        cfg.Detector2Radius, 
                                                        gRandom->Uniform(-cfg.Detector2Lenght/2.,cfg.Detector2Lenght/2.));
                NumberOfHits2++;
            }

            
            //save data and clear arrays for next collision
            tree->Fill();

            HitsDec1->Clear();
            HitsDec2->Clear();
            HitsVertex->Clear();
        
    }
    AssignedDist->Close();

    hfile.cd();
    tree->Write("", TObject::kOverwrite);
    hfile.Close();

    timer.Stop();
    timer.Print();

    delete HitsDec1;
    delete HitsDec2;
    delete HitsVertex;
    delete AssignedDist;

}