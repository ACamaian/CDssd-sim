#ifndef CDSSDRunActionMessenger_h
#define CDSSDRunActionMessenger_h 1

#include "G4UImessenger.hh"

class CDSSDRunAction;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWithoutParameter;

class CDSSDRunActionMessenger: public G4UImessenger {
private:
  CDSSDRunAction* runAction;     ///< Pointer to detector class

  G4UIdirectory*           actionDir;               ///< Directory in messenger structure
 
  G4UIcmdWithAString*        outputFileNameCmd;    

public:
  CDSSDRunActionMessenger(CDSSDRunAction* );
  ~CDSSDRunActionMessenger();

  void SetNewValue(G4UIcommand*, G4String);
};
#endif
