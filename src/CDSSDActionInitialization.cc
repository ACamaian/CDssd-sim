//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file CDSSDActionInitialization.cc
/// \brief Implementation of the DEMOActionInitialization class

#include "CDSSDActionInitialization.hh"
#include "CDSSDPrimaryGeneratorAction.hh"
#include "CDSSDRunAction.hh"
#include "CDSSDEventAction.hh"
#include "CDSSDDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDActionInitialization::CDSSDActionInitialization(CDSSDDetectorConstruction *detConstruction)
  : fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDActionInitialization::~CDSSDActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDActionInitialization::BuildForMaster() const
{ //needed by MultiThread Mode

  CDSSDEventAction *eventAction =0;
  CDSSDRunAction* runAction =new CDSSDRunAction(eventAction);
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDActionInitialization::Build() const
{

  //G4cout << "Primary Generator Action" << G4endl;
    auto generator = new CDSSDPrimaryGeneratorAction();
  SetUserAction(generator);
  
  //G4cout << "Event Action" << G4endl;
  CDSSDEventAction *eventAction = new CDSSDEventAction(generator, fDetConstruction);
  SetUserAction(eventAction); 
  
  // G4cout << "Run Action" << G4endl;
  CDSSDRunAction* runAction = new CDSSDRunAction(eventAction);
  SetUserAction(runAction);
  
  //G4cout << "Stepping Action" << G4endl;
  //  SetUserAction(new CDSSDSteppingAction(fDetConstruction, eventAction));


}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
