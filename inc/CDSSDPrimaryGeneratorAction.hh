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
#include "CDSSDGasDetectorConstruction.hh"

#include "CDSSDPrimaryGeneratorMessenger.hh"

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

  G4double GetThetaCMAngle(){return thetaCMAngle;}
  
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

  void SetVertexPosition(G4ThreeVector apos) {vertexPosition=apos;}
  G4ThreeVector GetVertexPosition(){return vertexPosition;}
  // end of corresponding Kine part

  void SetReactionQ(G4double val) { reactionQ = val;}
  void SetLabEnergy(G4double val) { labEnergy = val;}

  void SetThetaLabAngle(G4double val) { thetaLabAngle = val;}
  void SetVertexZPosition(G4double val) { vertexZPosition = val;} // vertex Z position, dypang 080704

  void SetRandomThetaVal(G4double min, G4double max) {
    randomThetaMin = min;
    randomThetaMax = max;
  }
  
  void SetRandomTheta(G4String ss) { randomTheta=ss;}

  void SetRandomPhiVal(G4double min, G4double max) {
    randomPhiMin = min;
    randomPhiMax = max;
  }

  void SetRandomVertexZPosition(G4String val) {randomVertexZPosition=val; }

  void SetRandomVertexZPositionVal(G4double min, G4double max) {
    randomVertexZPositionMin = min;
    randomVertexZPositionMax = max;
  }

  G4double GetRandomThetaMin() {return randomThetaMin;}
  G4double GetRandomThetaMax() {return randomThetaMax;}

  G4Ions* GetScatteredIon(){return scatteredIon;}
  G4Ions* GetRecoilIon(){return recoilIon;}
  G4double GetScatteredIonCharge(){return scatteredIonCharge;}
  G4double GetRecoilIonCharge(){return recoilIonCharge;}
  G4double GetReactionQ(){return reactionQ;}
  G4double GetLabEnergy(){return labEnergy;}
  G4double GetThetaLabAngle(){return thetaLabAngle;}
  G4double GetVertexZPosition(){return vertexZPosition;}

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

  //vertex
  G4String randomVertexZPosition;
  G4double randomVertexZPositionMin;  ///< Minimum value for the (random) Z position of the vertex
  G4double randomVertexZPositionMax;  ///< Maximum value for the (random) Z position of the vertex
  G4double vertexZPosition;           ///< Value for the (random) Z position of the vertex
  
  G4String randomTheta;
  G4double randomThetaMin;
  G4double randomPhiMin;
  G4double randomThetaMax;
  G4double randomPhiMax;

  //reaction global parameter
  G4double  thetaCMAngle;          ///< Center of mass polar angle
  G4double  userThetaAngle;        ///< User theta angle
  G4double  userPhiAngle;          ///< User phi angle
  G4double  massOfProjectile;      ///< Mass of the projectile ion
  G4double  massOfTarget;          ///< Mass of target ion
  G4double  massOfScattered;       ///< Mass of the scattered ion
  G4double  massOfRecoiled;        ///< Mass of the recoil ion
  G4double  exEnergyOfProjectile;  ///< Energy of the projectile ion
  G4double  exEnergyOfTarget;      ///< Energy of the target ion
  G4double  exEnergyOfScattered;   ///< Energy of the scattered ion
  G4double  exEnergyOfRecoiled;    ///< Energy of the recoil ion
  G4ThreeVector vertexPosition;    ///< Position of the vertex

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
