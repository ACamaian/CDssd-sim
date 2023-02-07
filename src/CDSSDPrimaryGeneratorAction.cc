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

#include <fstream>
#include <sstream>
#include <string>

#include <TMath.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDPrimaryGeneratorAction::CDSSDPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  particleGun(0), scatteredIon(0), recoilIon(0){
  
  G4cout << "Primary generator Construction" << G4endl;    
      
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

  uniformTheta = "off";
  thetaMin = 0.*deg;
  thetaMax = 80.*deg;
  
  singleTheta = "off";
  
  expoTheta="off";

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

  //--
  //At the first event , I'm reading the E* from a file if present
  //--
  if(GetEstarFromAFile()=="on"){
   if(estar_map.size()==0){ //not read yet
       estar_map = readEstarMap();
           }      
     }
  
  //---
  //Reaction Products: I generate only the reaction products, according to the set values for beam, and target
  //---
  
  //KINE object...
  CDSSDKine* KINE = new CDSSDKine();
  
  KINE->SetMassOfProjectile(GetMassOfProjectile());
  KINE->SetMassOfTarget(GetMassOfTarget());
  KINE->SetMassOfScattered(GetMassOfScattered());
  KINE->SetMassOfRecoiled(GetMassOfRecoiled());
  
  if(GetEstarFromAFile()=="on"){
  G4int r; 
  G4double w; 
  G4double x;
  do{
      r = G4UniformRand() * estar_map.size();
      w = estar_map[r][2];     
      x = G4UniformRand(); //0 to 1 
     }
     while(x>w); 
   SetExEnergyOfScattered(G4RandGauss::shoot(estar_map[r][0], estar_map[r][1]));       
  }
  KINE->SetExEnergyOfProjectile(GetExEnergyOfProjectile());
  KINE->SetExEnergyOfTarget(GetExEnergyOfTarget());
  KINE->SetExEnergyOfRecoiled(GetExEnergyOfRecoiled());
  KINE->SetExEnergyOfScattered(GetExEnergyOfScattered());
  
  KINE->SetLabEnergy(GetLabEnergy());

  //--
  //Reaction Cross Section shaping
  //--
  G4double thetacm_s=0;
  G4double xval=0, yval=0;

  //flat distribution between theta_min and theta_max
  if(uniformTheta=="on") {
      thetacm_s = (thetaMin +((thetaMax-thetaMin) * G4UniformRand())) * rad;
  }
  if(singleTheta=="on") {
      thetacm_s = GetThetaCMAngle();
  }
  if(expoTheta=="on") {
      do{
      thetacm_s = thetaMin + G4UniformRand()*(thetaMax-thetaMin);
      yval=GetExpoSigma0() * TMath::Exp(-thetacm_s/GetExpoVariance());     
      xval = (1000-0)*G4UniformRand(); //0 to 1 barn/str
     }
     while(xval>yval);
  }
  SetThetaCMAngle(thetacm_s);  
  KINE->SetThetaCMAngle(thetacm_s/deg);  // units: degree
  
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
  energyLab1    = KINE->GetANGAs(1);    // unit: MeV in LAB
  energyLab2    = KINE->GetANGAr(1);    // unit: MeV in LAB
  
  G4double phiBeam1=0., phiBeam2=0.;
   //G4cout << phiBeam1 << G4endl;
  if(uniformPhi=="on"){
    phiBeam1 = phiMin + (phiMax-phiMin)*G4UniformRand();         //flat probability in phi
    }
  if(singlePhi=="on"){
     phiBeam1 = GetPhiCMAngle();    
  }
  if(phiBeam1<TMath::Pi()) phiBeam2 = phiBeam1 + TMath::Pi();
    else  phiBeam2 = phiBeam1 - TMath::Pi();
    
  SetPhiCMAngle(phiBeam1);  
    
  thetaLab1 = thetaBeam1; //the scattered
  phiLab1   = phiBeam1; 
  
  thetaLab2 = thetaBeam2; //the recoil
  phiLab2   = phiBeam2; 

  
  delete KINE;
  
  if(verboseLevel>1){
    G4cout << "Kine: Scattered energy LAB:" << energyLab1 << " MeV" << G4endl;
    G4cout << "Kine: Recoiled energy LAB:" << energyLab2 << " MeV" << G4endl;
    G4cout << "Kine: Scattered angle LAB:"  << thetaLab1 / deg << " deg" << G4endl;
    G4cout << "Kine: recoiled  angle LAB:"  <<thetaLab2 / deg  << " deg" << G4endl;
    G4cout << "Kine: Scattered Phi angle LAB:"  << phiBeam1 /deg  << " deg" << G4endl;
    G4cout << "Kine: recoiled  Phi angle LAB:"  << phiBeam2 /deg  << " deg" << G4endl;
  }
  
  //-- Set the second gun to the desired vertex
  particleGun->SetParticlePosition(zero);

  //---Generating the primary vertex for recoil Ion
  G4ThreeVector direction2 = G4ThreeVector(sin(thetaLab2)*cos(phiLab2),
					   sin(thetaLab2)*sin(phiLab2),
					   cos(thetaLab2));
  particleGun->SetParticleDefinition(recoilIon);
  particleGun->SetParticleCharge(recoilIonCharge);
  particleGun->SetParticleMomentumDirection(direction2);
  particleGun->SetParticleEnergy(energyLab2);
  
  particleGun->GeneratePrimaryVertex(anEvent);
  
  //---
  //Decay of the scattered
  //--
//   if(inflightDecay=="on"){
//     G4double ex = GetExEnergyOfScattered();
//     if(emitUniform="on"){  
//         double thetapart = G4UniformRand()*M_PI;
//         double phipart = G4UniformRand()*2*M_PI;
//       
//         double zp = GetScatteredIon().charge;
//         double ap = GetScatteredIon().mass;
//         
//         G4double << zp << " " << ap << G4endl;
//     }
//   }
//   else{
  //---Generating the primary vertex for scattered Ion
  G4ThreeVector direction1 = G4ThreeVector(sin(thetaLab1)*cos(phiLab1),
					   sin(thetaLab1)*sin(phiLab1),
					   cos(thetaLab1));
  particleGun->SetParticleDefinition(scatteredIon);
  particleGun->SetParticleCharge(scatteredIonCharge);
  particleGun->SetParticleMomentumDirection(direction1);
  particleGun->SetParticleEnergy(energyLab1);
  particleGun->GeneratePrimaryVertex(anEvent);
 // }
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::map<int, std::vector<double>> CDSSDPrimaryGeneratorAction::readEstarMap(){
    
      std::ifstream in (GetEstarFileName(), std::ifstream::in);
      std::string line;
      int nlevel=0;
      
      if(!in.good()){
       G4cout << "Estar File not good: " << GetEstarFileName() << G4endl;   
      }
            
      std::map<int, std::vector<double>> map;
      
      while (getline(in,line)){
        if(line[0]=='#') continue;
        
        std::stringstream ss;
        ss.str(line);
        
        double estar, width, br;
        ss >> estar >> width >> br;
        
        std::vector<double> temp;
        temp.push_back(estar * keV);
        temp.push_back(width * keV);
        temp.push_back(br);
                
        map.emplace(nlevel, temp);
        nlevel++;
      }
      
      in.close();
      
      return map;
}
