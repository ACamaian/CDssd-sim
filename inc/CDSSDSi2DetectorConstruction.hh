#ifndef CDSSDSi2DetectorConstruction_h
#define CDSSDSi2DetectorConstruction_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4NistManager.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class CDSSDSi2DetectorMessenger;
class CDSSDDetectorConstruction;

class CDSSDSi2DetectorConstruction {
private:
   
  CDSSDSi2DetectorMessenger* si2Messenger;    ///< Pointer to the Messenger
  CDSSDDetectorConstruction* detConstruction; ///< Pointer to the global detector construction

  G4double si2Rmin;
  G4double si2Rmax;
  G4double si2RminActive;
  G4double si2RmaxActive;  
  G4double si2Thickness;
  G4double si2AlThickness;
  
  G4double si2NSlices;
  G4double DPhigap;
  G4double DPhisi;
  
  G4double res;
  
  G4double si2PosZ;  
  G4NistManager *nistman;

  G4LogicalVolume* motherSi2_log;       
    G4LogicalVolume* Si2Active_log;
  
  G4VPhysicalVolume* ConstructSi2(G4LogicalVolume*);

public:
  CDSSDSi2DetectorConstruction(CDSSDDetectorConstruction*);
  ~CDSSDSi2DetectorConstruction();

  G4VPhysicalVolume* Construct(G4LogicalVolume*);

  G4LogicalVolume* GetLogicalVolume(){return motherSi2_log;};
  G4LogicalVolume* GetActiveLogicalVolume(){return Si2Active_log;};
  
  
  void SetRmin(G4double val) {si2Rmin = val;}
  void SetRmax(G4double val) {si2Rmax = val;}
  void SetRminActive(G4double val) {si2RminActive = val;}
  void SetRmaxActive(G4double val) {si2RmaxActive = val;}
  void SetThickness(G4double val) {si2Thickness = val;}
  void SetAlThickness(G4double val) {si2AlThickness = val;}
  void SetZPos(G4double val) {si2PosZ = val;}
  void SetNSlices (G4double val) {si2NSlices = val;}    
  void SetDPhiGap (G4double val) {DPhigap = val;}
  void SetDPhiSi (G4double val) {DPhisi = val;}  
  
  void SetResolution(G4double val) {res=val;}
  
  G4double GetNSlices() {return si2NSlices;}
    
  G4double GetZPos(){return si2PosZ;}
  G4double GetThickness() {return si2Thickness;}
  G4double GetAlThickness() {return si2AlThickness;}
  
  G4double GetDPhiGap() {return DPhigap;}
  G4double GetDPhiSi() {return DPhisi;}  
  
  G4double GetRminActive(){return si2RminActive;}
  G4double GetRmaxActive(){return si2RmaxActive;}
  
  G4double GetResolution(){return res;}
  
};
#endif
