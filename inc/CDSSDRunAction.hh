/// \file CDSSDRunAction.hh
/// \brief Definition of the BRunAction class

#ifndef CDSSDRunAction_h
#define CDSSDRunAction_h 1

#include "CDSSDEventAction.hh"
#include "CDSSDRunActionMessenger.hh"
#include "G4AnalysisManager.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class CDSSDRunAction : public G4UserRunAction
{
public:
  CDSSDRunAction(CDSSDEventAction *event);
  ~CDSSDRunAction() override;
    
  void BeginOfRunAction(const G4Run*) override;
  void  EndOfRunAction(const G4Run*) override;
  
  void SetOutputFileName (G4String name) {outputFileName = name;}
  
  G4String GetOutputFileName(){return outputFileName;}
  
private:
  CDSSDEventAction *fEventAction = nullptr;
  CDSSDRunActionMessenger* runMessenger;

  G4String outputFileName;  
  
};

#endif

