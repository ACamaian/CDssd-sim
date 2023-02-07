/// \file B1PrimaryGeneratorAction.hh
/// \brief Definition of the B1PrimaryGeneratorAction class

#ifndef CDSSDPrimaryGeneratorAction_h
#define CDSSDPrimaryGeneratorAction_h 1

#include "G4VPrimaryGenerator.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "globals.hh"

#include "G4Event.hh"

#include "G4Ions.hh"
#include "G4IonTable.hh"

#include "CDSSDDetectorConstruction.hh"

#include "CDSSDPrimaryGeneratorMessenger.hh"

#include <map>
#include <vector>

class G4ParticleGun;
class G4Event;
class G4Box;


class CDSSDPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
  CDSSDPrimaryGeneratorAction();    
  virtual ~CDSSDPrimaryGeneratorAction();
  
  // method from the base class
  virtual void GeneratePrimaries(G4Event*);         
  
  
  void SetScatteredIon(G4Ions* aIonDef) { scatteredIon = aIonDef;}
  void SetRecoilIon(G4Ions* aIonDef) { recoilIon = aIonDef;}
  void SetScatteredIonCharge(G4double aCharge) { scatteredIonCharge = aCharge; }
  void SetRecoilIonCharge(G4double aCharge) { recoilIonCharge = aCharge; }
  
  //needed by KINE
  void SetThetaCMAngle(G4double val){thetaCMAngle=val; }
  void SetPhiCMAngle(G4double val){phiCMAngle=val; }

  G4double GetThetaCMAngle(){return thetaCMAngle;}
  G4double GetPhiCMAngle(){return phiCMAngle;}
  
  G4double GetThetaLabScattered(){return thetaLab1;}
  G4double GetPhiLabScattered(){return phiLab1;}
  G4double GetELabScattered(){return energyLab1;}
  G4double GetThetaLabRecoil(){return thetaLab2;}
  G4double GetPhiLabRecoil(){return phiLab2;}
  G4double GetELabRecoil(){return energyLab2;}
    
  void SetMassOfProjectile(G4double val){massOfProjectile=val;}
  void SetMassOfTarget(G4double val){massOfTarget=val;}
  void SetMassOfScattered(G4double val){massOfScattered=val;}
  void SetMassOfRecoiled(G4double val){massOfRecoiled=val;}

  G4double GetMassOfProjectile(){return massOfProjectile;}
  G4double GetMassOfTarget(){return massOfTarget;}
  G4double GetMassOfScattered(){return massOfScattered;}
  G4double GetMassOfRecoiled(){return massOfRecoiled;}

  void SetExEnergyOfProjectile(G4double val){exEnergyOfProjectile=val;}
  void SetExEnergyOfTarget(G4double val)    {exEnergyOfTarget=val;}
  void SetExEnergyOfScattered(G4double val) {exEnergyOfScattered=val;}
  void SetExEnergyOfRecoiled(G4double val)  {exEnergyOfRecoiled=val;}

  G4double GetExEnergyOfProjectile(){return exEnergyOfProjectile;}
  G4double GetExEnergyOfTarget()    {return exEnergyOfTarget;}
  G4double GetExEnergyOfScattered() {return exEnergyOfScattered;}
  G4double GetExEnergyOfRecoiled()  {return exEnergyOfRecoiled;}

  //Estar from a File
  void SetEstarFromAFile(G4String val){estarFromAFile=val;}
  void SetEstarFileName(G4String val){estarFileName=val;}
  G4String GetEstarFromAFile(){return estarFromAFile;}
  G4String GetEstarFileName(){return estarFileName;}
  
  // end of corresponding Kine part

  void SetReactionQ(G4double val) { reactionQ = val;}
  void SetLabEnergy(G4double val) { labEnergy = val;}

  void SetThetaLabAngle(G4double val) { thetaLabAngle = val;}

  void SetRandomTheta(G4String ss) {uniformTheta=ss;}
  void SetRandomThetaVal(G4double min, G4double max) {
    thetaMin = min;
    thetaMax = max;
  }
  void SetRandomPhi(G4String ss) {uniformPhi=ss;}
  void SetRandomPhiVal(G4double min, G4double max) {
    phiMin = min;
    phiMax = max;
  }  
  
  void SetExpoTheta(G4String ss) {expoTheta=ss;}
  void SetExpoThetaVal(G4double min, G4double max) {
    thetaMin = min;
    thetaMax = max;
  }
  void SetExpoParams(G4double sigma, G4double var){
    sigma0 = sigma;
    variance = var;      
  }
  G4double GetExpoVariance() {return variance;}
  G4double GetExpoSigma0() {return sigma0;}
  
  void SetSingleTheta(G4String ss) {singleTheta=ss;}
   void SetSinglePhi(G4String ss) {singlePhi=ss;}

  void SetThetaMin(G4double val) {thetaMin=val;}
  void SetThetaMax(G4double val) {thetaMax=val;}
  G4double GetThetaMin() {return thetaMin;}
  G4double GetThetaMax() {return thetaMax;}

  G4Ions* GetScatteredIon(){return scatteredIon;}
  G4Ions* GetRecoilIon(){return recoilIon;}
  G4double GetScatteredIonCharge(){return scatteredIonCharge;}
  G4double GetRecoilIonCharge(){return recoilIonCharge;}
  G4double GetReactionQ(){return reactionQ;}
  G4double GetLabEnergy(){return labEnergy;}
  
  G4double GetThetaLabAngle(){return thetaLabAngle;}

  void SetParticleDefinition(G4ParticleDefinition * aParticleDefinition) {particleGun->SetParticleDefinition(aParticleDefinition);}
  
  private:

  G4ParticleGun* particleGun;                       ///< Pointer to G4particleGun object initialized in constructor
 
  G4ParticleTable* particleTable;                   ///< Pointer to the G4ParticleTable
  G4IonTable* ionTable;                           ///< Pointer to the G4IonTable
  
  CDSSDPrimaryGeneratorMessenger* gunMessenger;  ///< Pointer to messenger

  G4Ions* scatteredIon;         ///< Pointer to scattered ion
  G4Ions* recoilIon;            ///< Pointer to recoil ion
  G4double scatteredIonCharge;  ///< Charge of scattered ion
  G4double recoilIonCharge;     ///< Charge of recoil ion

  G4double reactionQ;           ///< Reaction Q
  G4double labEnergy;           ///< Laboratory energy
  G4double thetaLabAngle;       ///< Polar angle in the laboratory system

  G4String uniformTheta;
  G4double thetaMin;
  G4double thetaMax;
  
  G4String uniformPhi;
  G4double phiMin;
  G4double phiMax;
  
  G4String expoTheta;  
  G4double variance;
  G4double sigma0;
  
  G4String singleTheta;
  G4String singlePhi;
  
  //reaction global parameter
  G4double  thetaCMAngle;          ///< Center of mass polar angle
  G4double  phiCMAngle;          ///< Center of mass azimuthal angle
  G4double  massOfProjectile;      ///< Mass of the projectile ion
  G4double  massOfTarget;          ///< Mass of target ion
  G4double  massOfScattered;       ///< Mass of the scattered ion
  G4double  massOfRecoiled;        ///< Mass of the recoil ion
  G4double  exEnergyOfProjectile;  ///< Energy of the projectile ion
  G4double  exEnergyOfTarget;      ///< Energy of the target ion
  G4double  exEnergyOfScattered;   ///< Energy of the scattered ion
  G4double  exEnergyOfRecoiled;    ///< Energy of the recoil ion
  
  G4double energyLab1;
  G4double thetaLab1;
  G4double phiLab1;
  G4double energyLab2;
  G4double thetaLab2;
  G4double phiLab2;
  
  G4String estarFromAFile;
  G4String estarFileName;
  
  std::map<int, std::vector<double>> readEstarMap();
  std::map<int, std::vector<double>> estar_map;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
