#ifndef CDSSDSi2DetectorMessenger_h
#define CDSSDSi2DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CDSSDSi2DetectorConstruction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;

class CDSSDSi2DetectorMessenger: public G4UImessenger {

private:

    
    
  CDSSDSi2DetectorConstruction* CDSSDSi2Detector;         ///< Pointer to detector geometry class

  G4UIdirectory*             si2Dir;                      ///< Directory

  G4UIcmdWithADoubleAndUnit *RminCmd;
  G4UIcmdWithADoubleAndUnit *RmaxCmd;
  G4UIcmdWithADoubleAndUnit *RminActiveCmd;
  G4UIcmdWithADoubleAndUnit *RmaxActiveCmd;
  G4UIcmdWithADoubleAndUnit *thickCmd;
  G4UIcmdWithADoubleAndUnit *thickAlCmd;
  G4UIcmdWithADoubleAndUnit *zPosCmd;
  G4UIcmdWithADouble *nSlicesCmd;
  G4UIcmdWithADoubleAndUnit *dPhiGapCmd;
  G4UIcmdWithADoubleAndUnit *dPhiSiCmd;
  
  G4UIcmdWithADouble *resCmd;
  
  void SetNewValue(G4UIcommand*, G4String);

public:
  CDSSDSi2DetectorMessenger(CDSSDSi2DetectorConstruction*);
  ~CDSSDSi2DetectorMessenger();

};
#endif
