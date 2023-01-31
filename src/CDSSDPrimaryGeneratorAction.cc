//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
/// \file CDSSDPrimaryGeneratorAction.cc
/// \brief Implementation of the CDSSDPrimaryGeneratorAction class

#include "CDSSDPrimaryGeneratorAction.hh"
#include "CDSSDPrimaryGeneratorMessenger.hh"

#include "CDSSDKine.hh"
// #include "CDSSDEulerTransformation.hh"

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
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

  thetaLabAngle = 45 * deg;   // 45 degrees (TH)
  thetaCMAngle = 45 * deg;

  randomTheta = "off";
  randomThetaMin = 0.*deg;
  randomThetaMax = 180.*deg;

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
  
  //KINE object...
  CDSSDKine* KINE = new CDSSDKine();
  
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
    G4cout << " KINE: Setting (atomic) masses to :" << GetMassOfProjectile()
	   << " " << GetMassOfTarget()
	   << " " << GetScatteredIon()->GetAtomicMass()
	   << " " << GetRecoilIon()->GetAtomicMass()<< " "<< G4endl;
    G4cout << " KINE: Setting labEnergy to:" << KINE->GetLabEnergy() << G4endl;
    G4cout << " KINE: Setting targetExcitationEnergy to:"
	   << GetExEnergyOfTarget() << G4endl;
    G4cout << " KINE: Setting projectileExcitationEnergy to:"
	   << GetExEnergyOfProjectile() << G4endl;
    G4cout << " Kine: Setting excitation energy of Scattered particle to:"
	   << GetScatteredIon()->GetExcitationEnergy() << G4endl;
    G4cout << " KINE: Setting CM Angle to:" << GetThetaCMAngle()/deg << " deg" << G4endl;
  }
  
  //Calling the relativistic kinematic calculation
  KINE->KineKinematics();
  
  if(KINE->GetNoSolution()) G4cout << "Kine NO solution, check your input!" << G4endl;
  
  G4double thetaBeam1, thetaBeam2;
  thetaBeam1 = KINE->GetANGAs(0);    // unit: rad- scattered in LAB
  thetaBeam2 = KINE->GetANGAr(0);    // unit: rad - recoil in LAB
  energy1    = KINE->GetANGAs(1);    // unit: MeV in LAB
  energy2    = KINE->GetANGAr(1);    // unit: MeV in LAB
  
  G4double phiBeam1=0., phiBeam2=0.;
  phiBeam1 = GetPhiCMAngle();
  G4cout << phiBeam1 << G4endl;
  //phiBeam1 = GetPhi2*TMath::Pi() * G4UniformRand();         //flat probability in phi
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
    G4cout << "Kine: Scattered Phi angle LAB:"  << phiBeam1 /deg  << " deg" << G4endl;
    G4cout << "Kine: recoiled  Phi angle LAB:"  << phiBeam2 /deg  << " deg" << G4endl;
  }
  
  //-- Set the second gun to the desired vertex
  particleGun->SetParticlePosition(zero);

  //---Generating the primary vertex for scattered Ion
  G4ThreeVector direction1 = G4ThreeVector(sin(thetaLab1)*cos(phiLab1),
					   sin(thetaLab1)*sin(phiLab1),
					   cos(thetaLab1));
  particleGun->SetParticleDefinition(scatteredIon);
  particleGun->SetParticleCharge(scatteredIonCharge);
  particleGun->SetParticleMomentumDirection(direction1);
  particleGun->SetParticleEnergy(energy1);
  
  particleGun->GeneratePrimaryVertex(anEvent);

  //---Generating the primary vertex for recoil Ion
  G4ThreeVector direction2 = G4ThreeVector(sin(thetaLab2)*cos(phiLab2),
					   sin(thetaLab2)*sin(phiLab2),
					   cos(thetaLab2));
  particleGun->SetParticleDefinition(recoilIon);
  particleGun->SetParticleCharge(recoilIonCharge);
  particleGun->SetParticleMomentumDirection(direction2);
  particleGun->SetParticleEnergy(energy2);
  
  particleGun->GeneratePrimaryVertex(anEvent);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

