#ifndef CDSSDPhysListParticles_h
#define CDSSDPhysListParticles_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CDSSDPhysListParticles : public G4VPhysicsConstructor
{
  public: 
    CDSSDPhysListParticles(const G4String& name = "particles");
   ~CDSSDPhysListParticles();

  public: 
    // This method will be invoked in the Construct() method. 
    // each particle type will be instantiated
    void ConstructParticle();
 
    // This method is dummy.
    void ConstructProcess() {};

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif








