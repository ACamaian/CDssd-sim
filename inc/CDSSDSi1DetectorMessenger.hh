#ifndef CDSSDSi1DetectorMessenger_h
#define CDSSDSi1DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CDSSDSi1DetectorConstruction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;

class CDSSDSi1DetectorMessenger: public G4UImessenger {

private:

    
    
  CDSSDSi1DetectorConstruction* CDSSDSi1Detector;         ///< Pointer to detector geometry class

  G4UIdirectory*             si1Dir;                      ///< Directory

  G4UIcmdWithADoubleAndUnit *RminCmd;
  G4UIcmdWithADoubleAndUnit *RmaxCmd;
  G4UIcmdWithADoubleAndUnit *RminActiveCmd;
  G4UIcmdWithADoubleAndUnit *RmaxActiveCmd;
  G4UIcmdWithADoubleAndUnit *thickCmd;
  G4UIcmdWithADoubleAndUnit *thickAlCmd;
  G4UIcmdWithADoubleAndUnit *zPosCmd;

  G4UIcmdWithADouble *nSlicesCmd;
  G4UIcmdWithADouble *nRadialCmd;
  G4UIcmdWithADouble *nAziCmd;

  G4UIcmdWithADoubleAndUnit *dPhiGapCmd;
  G4UIcmdWithADoubleAndUnit *dPhiSiCmd;
  
  G4UIcmdWithADouble *resCmd;
  
  
  void SetNewValue(G4UIcommand*, G4String);

public:
  CDSSDSi1DetectorMessenger(CDSSDSi1DetectorConstruction*);
  ~CDSSDSi1DetectorMessenger();

};
#endif
