/// \file CDSSDActionInitialization.hh
/// \brief Definition of the CDSSDActionInitialization class

#ifndef CDSSDActionInitialization_h
#define CDSSDActionInitialization_h 1

#include "CDSSDDetectorConstruction.hh"

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class CDSSDActionInitialization : public G4VUserActionInitialization
{
  public:
    CDSSDActionInitialization(CDSSDDetectorConstruction *);
    ~CDSSDActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;

private:
  CDSSDDetectorConstruction *fDetConstruction = nullptr;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
