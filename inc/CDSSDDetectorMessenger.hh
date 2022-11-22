#ifndef CDSSDDetectorMessenger_h
#define CDSSDDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CDSSDDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWithoutParameter;

class CDSSDDetectorMessenger: public G4UImessenger {
private:
  CDSSDDetectorConstruction* CDSSDDetector;     ///< Pointer to detector class

  G4UIdirectory*             CDSSDDir;             ///< Directory in messenger structure
  G4UIdirectory*             detDir;               ///< Directory in messenger structure
 
  G4UIcmdWithAString*        targetMaterialCmd;    
  G4UIcmdWithADoubleAndUnit* targetThicknessCmd;     

public:
  CDSSDDetectorMessenger(CDSSDDetectorConstruction* );
  ~CDSSDDetectorMessenger();

  void SetNewValue(G4UIcommand*, G4String);
  //G4String GetCurrentValue(G4UIcommand*);
};
#endif
