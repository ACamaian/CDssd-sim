#ifndef CDSSDDetectorConstruction_h
#define CDSSDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"

#include "G4UserLimits.hh"

class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4AssemblyVolume;

class CDSSDDetectorMessenger;
class CDSSDSi1DetectorConstruction;
class CDSSDSi1SD;

class CDSSDSi2DetectorConstruction;
class CDSSDSi2SD;

class CDSSDDetectorConstruction : public G4VUserDetectorConstruction {
private:
    
  G4UserLimits* limit;

  G4Box* solidWorld;
  G4LogicalVolume* worldLog;      ///< Pointer to logic world
  G4VPhysicalVolume* worldPhys;   ///< Pointer to physical world
    
  G4double worldSizeX;    ///< World X half-lengths (always centered at (0,0,0))
  G4double worldSizeY;    ///< World Y half-lengths (always centered at (0,0,0))
  G4double worldSizeZ;    ///< World Z half-lengths (always centered at (0,0,0))

  G4Material *vacuumMaterial;
  G4Material *targetMaterial;
  G4double  targetThickness;
  
  CDSSDSi1DetectorConstruction* si1Det;          ///< Pointer to target constructor 
  CDSSDSi2DetectorConstruction* si2Det;          ///< Pointer to target constructor 
    
  CDSSDDetectorMessenger* detectorMessenger;  ///< Pointer to the Messenger

  void DefineMaterials();
  G4VPhysicalVolume* ConstructEmptyWorld();
  G4VPhysicalVolume* ConstructCDSSD();

public:
  CDSSDDetectorConstruction();
  ~CDSSDDetectorConstruction() override;

  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

  void SetWorldSizeX(G4double val){worldSizeX = val;}
  void SetWorldSizeY(G4double val){worldSizeY = val;}
  void SetWorldSizeZ(G4double val){worldSizeZ = val;}
  
  void SetTargetThickness (G4double val){targetThickness = val;}
  void SetTargetMaterial (G4String mat);
 
  CDSSDDetectorMessenger* GetDetectorMessenger(){return detectorMessenger;};

  G4LogicalVolume* GetWorldLogicalVolume(){return worldLog;}
  G4VPhysicalVolume* GetWorldPhysicalVolume(){return worldPhys;}

  G4double GetWorldSizeX(void){return worldSizeX;}
  G4double GetWorldSizeY(void){return worldSizeY;}
  G4double GetWorldSizeZ(void){return worldSizeZ;}

  CDSSDSi1DetectorConstruction* GetSi1Detector() {return si1Det;}
  CDSSDSi2DetectorConstruction* GetSi2Detector() {return si2Det;}
  
 
  
  void UpdateGeometry();
    
};
#endif
