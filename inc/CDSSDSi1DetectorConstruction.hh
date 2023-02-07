#ifndef CDSSDSi1DetectorConstruction_h
#define CDSSDSi1DetectorConstruction_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4NistManager.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class CDSSDSi1DetectorMessenger;
class CDSSDDetectorConstruction;

class CDSSDSi1DetectorConstruction {
private:
   
  CDSSDSi1DetectorMessenger* si1Messenger;    ///< Pointer to the Messenger
  CDSSDDetectorConstruction* detConstruction; ///< Pointer to the global detector construction

  G4double si1Rmin;
  G4double si1Rmax;
  G4double si1RminActive;
  G4double si1RmaxActive;  
  G4double si1Thickness;
  G4double si1AlThickness;
    
  G4double si1NSlices;
  G4double DPhigap;
  G4double DPhisi;
  
  G4double si1NRadialStrips;
  G4double si1NAzimuthalStrips;
  
  G4double res;
  
  G4double si1PosZ;  
  G4NistManager *nistman;

  G4LogicalVolume* motherSi1_log;      
  G4LogicalVolume* Si1Active_log; 

  G4VPhysicalVolume* ConstructSi1(G4LogicalVolume*);

public:
  CDSSDSi1DetectorConstruction(CDSSDDetectorConstruction*);
  ~CDSSDSi1DetectorConstruction();

  G4VPhysicalVolume* Construct(G4LogicalVolume*);

  G4LogicalVolume* GetActiveLogicalVolume(){return Si1Active_log;};
  
  void SetRmin(G4double val) {si1Rmin = val;}
  void SetRmax(G4double val) {si1Rmax = val;}
  void SetRminActive(G4double val) {si1RminActive = val;}
  void SetRmaxActive(G4double val) {si1RmaxActive = val;}
  void SetThickness(G4double val) {si1Thickness = val;}
  void SetAlThickness(G4double val) {si1AlThickness = val;}
  void SetZPos(G4double val) {si1PosZ = val;}
  void SetNSlices (G4double val) {si1NSlices = val;}    
  void SetDPhiGap (G4double val) {DPhigap = val;}
  void SetDPhiSi (G4double val) {DPhisi = val;}  
  
  void SetNRadialStrips (G4double val) {si1NRadialStrips = val;}
  void SetNAzimuthalStrips (G4double val) {si1NAzimuthalStrips = val;}
  
  void SetResolution (G4double val) {res=val;}
  
  G4double GetNSlices() {return si1NSlices;}
  G4double GetNRadialStrips() {return si1NRadialStrips;}
  G4double GetNAzimuthalStrips() {return si1NAzimuthalStrips;}
  
  G4double GetZPos(){return si1PosZ;}
  G4double GetThickness() {return si1Thickness;}
  G4double GetAlThickness() {return si1AlThickness;}
  
  G4double GetDPhiGap() {return DPhigap;}
  G4double GetDPhiSi() {return DPhisi;}  
  
  G4double GetRminActive(){return si1RminActive;}
  G4double GetRmaxActive(){return si1RmaxActive;}
  
  G4double GetResolution(){return res;}
};
#endif
