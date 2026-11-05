#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>
#include <TEnv.h>

struct Config {
    double BeamPipeRadius;
    double BeamPipeThickness;
    double BeamPipeRadiationLenght;

    double Detector1Radius;
    double Detector1Lenght;
    double Detector1Thickness;
    double Detector1RadiationLenght;

    double Detector2Radius;
    double Detector2Lenght;

    double ArcSmearing;
    double ZSmearing;

    double ParticleMomentum; //In MeV/c
    bool MultipleScattering;

    int SelectMolteplicity; //0= Uniform, 1 = Distribuzione assegnata
    int SelectPseudoRapidity; //0= Uniform, 1 = Distribuzione assegnata
    int MaxUniformMolteplicity;

    int LevelOfNoise;

    double CollisionZRms;
    double CollisionXRms;
    double CollisionYRms;

    int NumberOfEvents;
    int Seed;

};

// 2. Funzione che legge il file tramite TEnv
inline Config LoadSettings(const std::string& File) {
    TEnv env(File.c_str());
    Config cfg;

    cfg.BeamPipeRadius = env.GetValue("BeamPipeRadius", 3);
    cfg.BeamPipeThickness = env.GetValue("BeamPipeThickness", 0.08);

    cfg.Detector1Lenght = env.GetValue("Detector1Lenght", 27);
    cfg.Detector2Lenght = env.GetValue("Detector2Lenght", 27);

    cfg.Detector1Radius = env.GetValue("Detector1Radius", 4);
    cfg.Detector2Radius = env.GetValue("Detector2Radius", 7);

    cfg.Detector1Thickness = env.GetValue("Detector1Thickness", 0.02);

    cfg.BeamPipeRadiationLenght = env.GetValue("BeamPipeRadiationLenght", 35.28);
    cfg.Detector1RadiationLenght = env.GetValue("Detector1RadiationLenght", 9.37);

    cfg.CollisionXRms = env.GetValue("CollisionXRms", 0.01);
    cfg.CollisionYRms = env.GetValue("CollisionYRms", 0.01);
    cfg.CollisionZRms = env.GetValue("CollisionZRms", 5.3);

    cfg.ParticleMomentum = env.GetValue("ParticleMomentum", 900);

    cfg.ArcSmearing = env.GetValue("ArcSmearing", 0.0120);
    cfg.ZSmearing = env.GetValue("ZSmearing", 0.03);

    cfg.MultipleScattering = env.GetValue("MultipleScattering", true);
    cfg.SelectPseudoRapidity = env.GetValue("SelectPseudoRapidity", 1);
    cfg.SelectMolteplicity = env.GetValue("SelectMolteplicity", 1);
    cfg.MaxUniformMolteplicity = env.GetValue("MaxUniformMolteplicity", 60);

    cfg.LevelOfNoise = env.GetValue("LevelOfNoise", 3);

    cfg.NumberOfEvents = env.GetValue("NumberOfEvents", 1e06);
    cfg.Seed = env.GetValue("Seed",0);
    return cfg;
}
#endif