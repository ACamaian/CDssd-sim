//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
/// \file CDSSDPrimaryGeneratorAction.cc
/// \brief Implementation of the CDSSDPrimaryGeneratorAction class

#include "CDSSDPrimaryGeneratorAction.hh"
#include "CDSSDPrimaryGeneratorMessenger.hh"

#include "CDSSDKinePrimGenerator.hh"
#include "CDSSDEulerTransformation.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <TMath.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDPrimaryGeneratorAction::CDSSDPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  particleGun(0), scatteredIon(0), recoilIon(0){
  
  G4ThreeVector zero;
  particleTable = G4ParticleTable::GetParticleTable();
  ionTable = G4IonTable::GetIonTable();
  
  particleGun  = new G4ParticleGun(1);

  G4ParticleDefinition *pd = particleTable->FindParticle("proton");
  if(pd != 0)  particleGun->SetParticleDefinition(pd);
  particleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  particleGun->SetParticleCharge(1.0);
  particleGun->SetParticleEnergy(1*MeV);
  particleGun->SetParticleDirection(G4ThreeVector(0,0,1));

  thetaLabAngle = 45 * deg;   // 45 degrees (TH)

  thetaCMAngle = 45 * deg;
  randomThetaMin = 0.*deg;
  randomThetaMax = 180.*deg;

  vertexZPosition = 0 *mm;

  //building the messenger
  gunMessenger = new CDSSDPrimaryGeneratorMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDPrimaryGeneratorAction::~CDSSDPrimaryGeneratorAction()
{
  if(particleGun!=NULL) delete particleGun;  
  if(gunMessenger!=NULL) delete gunMessenger; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  
  const G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
  if(verboseLevel>0)
    G4cout << G4endl << " _____ G4RunManager VerboseLevel = " <<verboseLevel<< G4endl;

  G4ThreeVector zero;

  //---
  //Reaction Products: I generate only the reaction products, according to the set values for beam, and target
  //---
  
 
  G4double theta1=0.;
  G4double theta2=0.;
  G4double energy1=0.;
  G4double energy2=0.;
  
  // vertex_z0 decides the z position of the vertex. The beam is tracked till vertex_z0 is reached ...
  G4double vertex_z0 = 0;
  
  if(randomVertexZPosition=="off"){
    vertex_z0 = vertexZPosition;
  }
  else if(randomVertexZPosition=="on"){
    vertex_z0 = randomVertexZPositionMin + G4UniformRand()*(randomVertexZPositionMax-randomVertexZPositionMin);
  }  

  //KINE object...
  CDSSDKinePrimGenerator* KINE = new CDSSDKinePrimGenerator();
  
  KINE->SetMassOfProjectile(GetMassOfProjectile());
  KINE->SetMassOfTarget(GetMassOfTarget());
  KINE->SetMassOfScattered(GetMassOfScattered());
  KINE->SetMassOfRecoiled(GetMassOfRecoiled());
  
  KINE->SetExEnergyOfProjectile(GetExEnergyOfProjectile());
  KINE->SetExEnergyOfTarget(GetExEnergyOfTarget());
  KINE->SetExEnergyOfScattered(GetExEnergyOfScattered());
  KINE->SetExEnergyOfRecoiled(GetExEnergyOfRecoiled());
  
  KINE->SetLabEnergy(GetLabEnergy());

  //flat distribution between theta_min and theta_max
  if(randomTheta=="on") SetThetaCMAngle((randomThetaMin +((randomThetaMax-randomThetaMin) * G4UniformRand())) * rad);
  else if(randomTheta=="off"){}  
  //if we want to set the theta according to a given function we have to do it here
  
  KINE->SetThetaCMAngle(GetThetaCMAngle()/deg);  // units: degree
  
  if(verboseLevel>1){
    G4cout << " KINE: Setting (atomic) masses to :" << GetIncidentIon()->GetAtomicMass()
	   << " " << GetTargetIon()->GetAtomicMass()
	   << " " << GetScatteredIon()->GetAtomicMass()
	   << " " << GetRecoilIon()->GetAtomicMass()<< " "<< G4endl;
    G4cout << " KINE: Setting labEnergy to:" << KINE->GetLabEnergy() << G4endl;
    G4cout << " KINE: Setting targetExcitationEnergy to:"
	   << GetTargetIon()->GetExcitationEnergy() << G4endl;
    G4cout << " KINE: Setting projectileExcitationEnergy to:"
	   << GetIncidentIon()->GetExcitationEnergy() << G4endl;
    G4cout << " Kine: Setting excitation energy of Scattered particle to:"
	   << GetScatteredIon()->GetExcitationEnergy() << G4endl;
    G4cout << " KINE: Setting CM Angle to:" << GetThetaCMAngle()/deg << " deg" << G4endl;
  }
  
  //Calling the relativistic kinematic calculation
  KINE->KineKinematics();
  
  if(KINE->GetNoSolution()) G4cout << "Kine NO solution, check your input!" << G4endl;
  
  G4double thetaBeam1, thetaBeam2;
  thetaBeam1 = KINE->GetANGAs(0);    // unit: rad- scattered 
  thetaBeam2 = KINE->GetANGAr(0);    // unit: rad - recoil
  energy1    = KINE->GetANGAs(1);    // unit: MeV
  energy2    = KINE->GetANGAr(1);    // unit: MeV
  
  if(verboseLevel>1){
    G4cout << "Kine: Scattered energy CM:" << KINE->GetANGAs(1) << " MeV" << G4endl;
    G4cout << "Kine: Recoiled energy CM:" << KINE->GetANGAr(1) << " MeV" << G4endl;
    G4cout << "Kine: Scattered angle CM:"  << KINE->GetANGAs(0)/deg << " deg" << G4endl;
    G4cout << "Kine: recoiled  angle CM:"  << KINE->GetANGAr(0)/deg << " deg" << G4endl;
  }

  G4double phiBeam1=0., phiBeam2=0.;
  phiBeam1 = 2*TMath::Pi() * G4UniformRand();         //flat probability in phi
  if(phiBeam1<TMath::Pi()) phiBeam2 = phiBeam1 + TMath::Pi();
  else  phiBeam2 = phiBeam1 - TMath::Pi();
  
  thetaLab1 = thetaBeam1;
  phiLab1   = phiBeam1; 
  
  thetaLab2 = thetaBeam2;
  phiLab2   = phiBeam2; 

  delete KINE;
  
  if(verboseLevel>1){
    G4cout << "Kine: Scattered energy LAB:" << energy1 << " MeV" << G4endl;
    G4cout << "Kine: Recoiled energy LAB:" << energy2 << " MeV" << G4endl;
    G4cout << "Kine: Scattered angle LAB:"  << thetaLab1 / deg << " deg" << G4endl;
    G4cout << "Kine: recoiled  angle LAB:"  <<thetaLab2 / deg  << " deg" << G4endl;
  }
  
  //-- Set the second gun to the desired vertex
  prodGun->SetParticlePosition(G4ThreeVector(0.0,0.0,vertex_z0));

  //---Generating the primary vertex for scattered Ion
  G4ThreeVector direction1 = G4ThreeVector(sin(thetaLab1)*cos(phiLab1),
					   sin(thetaLab1)*sin(phiLab1),
					   cos(thetaLab1));
  prodGun->SetParticleDefinition(scatteredIon);
  prodGun->SetParticleCharge(scatteredIonCharge);
  prodGun->SetParticleMomentumDirection(direction1);
  prodGun->SetParticleEnergy(energy1);
  
  prodGun->GeneratePrimaryVertex(anEvent);

  //---Generating the primary vertex for recoil Ion
  G4ThreeVector direction2 = G4ThreeVector(sin(thetaLab2)*cos(phiLab2),
					   sin(thetaLab2)*sin(phiLab2),
					   cos(thetaLab2));
  prodGun->SetParticleDefinition(recoilIon);
  prodGun->SetParticleCharge(recoilIonCharge);
  prodGun->SetParticleMomentumDirection(direction2);
  prodGun->SetParticleEnergy(energy2);
  
  prodGun->GeneratePrimaryVertex(anEvent);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

