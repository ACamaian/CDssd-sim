#ifndef CDSSDSi1DetectorMessenger_h
#define CDSSDSi1DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CDSSDSi1DetectorConstruction;
class CDSSDSi1DetectorConstruction;
//class ActarSimPrimaryGeneratorAction;

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

  CDSSDSi1DetectorConstruction* Si1Detector;         ///< Pointer to main detector geometry class
  CDSSDSi1DetectorConstruction* CDSSDSi1Detector;   ///< Pointer to main gas detector geometry class

  G4UIdirectory*             si1Dir;                      ///< Directory

  void SetNewValue(G4UIcommand*, G4String);

public:
  CDSSDSi1DetectorMessenger(CDSSDSi1DetectorConstruction*);
  ~CDSSDSi1DetectorMessenger();

};
#endif
