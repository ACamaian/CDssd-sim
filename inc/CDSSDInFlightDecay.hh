#ifndef CDSSDInFlightDecay_h
#define CDSSDInFlightDecay_h 11

#include "G4ThreeVector.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "G4Ions.hh"
#include "G4IonTable.hh"

#include <map>
#include <string>
#include <tuple>

class CDSSDInFlightDecay {
private:
    
    double qgs=0;
    
    double estarparent=0;
    double zparent=0;
    double aparent=0;
    G4ThreeVector vlab_parent;
    
    G4Ions* daughterDef;
    double estardaughter=0;
    double zdaughter=0;
    double adaughter=0;
    G4ThreeVector vdaughter;
    G4ThreeVector vlab_daughter;
    
    G4Ions* emittedDef;
    double zemitted=0;
    double aemitted=0;
    G4ThreeVector vemitted;
    G4ThreeVector vlab_emitted;

    std::map<int, double> mass_defect;
    
    std::string decay_scheme_file_name;
    std::map<int, std::tuple<double, double, double, double, double, double, std::string> > decay_scheme;
    
public:
     CDSSDInFlightDecay(std::string filename);
  ~CDSSDInFlightDecay();
    
  //parent

  void SetParentMass(double aa){aparent=aa;}
  void SetParentCharge(double aa){zparent=aa;}
  void SetParentLabVelocity(G4ThreeVector vv){
        vlab_parent.setX( vv[0]);
        vlab_parent.setY( vv[1]);
        vlab_parent.setZ( vv[2]);
        }
  void SetParentEstar(double aa){estarparent = aa;}
  void SetParent(double aa, double zz, G4ThreeVector vv, double es){
    SetParentMass(aa);
    SetParentCharge(zz);
    SetParentLabVelocity(vv);
    SetParentEstar(es);
  }
   G4ThreeVector GetParentLabVelocity(){ return vdaughter;}
  
  //daughter
  
  void SetDaughterDef(G4Ions *aIonDef){daughterDef=aIonDef;}
  void SetDaughterMass(double aa){adaughter=aa;}
  void SetDaughterCharge(double aa){zdaughter=aa;}
  void SetDaughterLabVelocity(G4ThreeVector vv){
        vlab_daughter.setX( vv[0]);
        vlab_daughter.setY( vv[1]);
        vlab_daughter.setZ( vv[2]);
        }
  void SetDaughterVelocity(G4ThreeVector vv){
        vdaughter.setX( vv[0]);
        vdaughter.setY( vv[1]);
        vdaughter.setZ( vv[2]);
        }
  void SetDaughterEstar(double aa){estardaughter = aa;}
  void SetDaughter(double aa, double zz, G4ThreeVector vv, double es){
    SetDaughterMass(aa);
    SetDaughterCharge(zz);
    SetDaughterVelocity(vv);
    SetDaughterEstar(es);
  }
  G4ThreeVector GetDaughterLabVelocity(){ return vlab_daughter;}
  double GetDaughterMass(){return adaughter;}
  double GetDaughterCharge(){return zdaughter;}
  G4Ions* GetParticleDefinitionDaughter(){return daughterDef;}
  double GetDaughterLabEkin(){return 0.5 * adaughter * 931.5 * pow(vlab_daughter.mag()/300.,2);}
  
  //emitted
  
  void SetEmittedDef(G4Ions *aIonDef){emittedDef=aIonDef;}
  void SetEmittedMass(double aa){aemitted=aa;}
  void SetEmittedCharge(double aa){zemitted=aa;}
  void SetEmittedLabVelocity(G4ThreeVector vv){
        vlab_emitted.setX( vv[0]);
        vlab_emitted.setY( vv[1]);
        vlab_emitted.setZ( vv[2]);
        }
  void SetEmittedVelocity(G4ThreeVector vv){
        vemitted.setX( vv[0]);
        vemitted.setY( vv[1]);
        vemitted.setZ( vv[2]);
        }
  void SetEmitted(double aa, double zz, G4ThreeVector vv){
      SetEmittedMass(aa);
    SetEmittedCharge(zz);
    SetEmittedVelocity(vv);
  }
  G4ThreeVector GetEmittedLabVelocity(){ return vlab_emitted;}
  double GetEmittedMass(){return aemitted;}
  double GetEmittedCharge(){return zemitted;}
  G4Ions* GetParticleDefinitionEmitted(){return emittedDef;}
  double GetEmittedLabEkin(){return 0.5 * aemitted * 931.5 * pow(vlab_emitted.mag()/300.,2);}
  
  int GetNDecays() {return decay_scheme.size();}
  double GetCoulombRepulsion();
  
  std::map<int, std::tuple<double, double, double, double, double, double, std::string> > GetDecayScheme();  
  std::string GetDecaySchemeFileName(){return decay_scheme_file_name;}
  
  void InitADecay(int idec, G4ThreeVector vlab);
  void FromCMToLab();
  void ComputeADecay();
  void PrintADecay();
  
  
};
#endif
