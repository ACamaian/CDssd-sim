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

  G4double si1BoxSizeX;
  G4double si1BoxSizeY;
  G4double si1BoxSizeZ;

  G4double si1BoxCenterX;
  G4double si1BoxCenterY;
  G4double si1BoxCenterZ;

  G4NistManager *nistman;

  G4LogicalVolume* si1Log;       

  G4VPhysicalVolume* ConstructSi1(G4LogicalVolume*);

public:
  CDSSDSi1DetectorConstruction(CDSSDDetectorConstruction*);
  ~CDSSDSi1DetectorConstruction();

  G4VPhysicalVolume* Construct(G4LogicalVolume*);

  G4LogicalVolume* GetLogicalVolume(){return si1Log;};
};
#endif
