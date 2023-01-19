#include "CDSSDSi1DetectorConstruction.hh"
#include "CDSSDDetectorConstruction.hh"
#include "CDSSDSi1DetectorMessenger.hh"
#include "CDSSDSi1SD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "G4Transform3D.hh"

#include "G4Region.hh"

#include "globals.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//////////////////////////////////////////////////////////////////
/// Constructor
/// Sets the material and the pointer to the Messenger
CDSSDSi1DetectorConstruction::
CDSSDSi1DetectorConstruction(CDSSDDetectorConstruction* det)
  :	detConstruction(det){

  G4cout << "CDSSD Si1 Detector Construction" << G4endl;

  //Intialize the Nistmanager
  nistman = G4NistManager::Instance();

  //si1 Box size (half lenght)
  si1BoxSizeX = 10.*mm; 
  si1BoxSizeY = 10.*mm; 
  si1BoxSizeZ = 10.*mm;
  
  //Pad Size : GasBox height from chamber floor = 4.54mm
  si1BoxCenterX = 0.*mm;
  si1BoxCenterY = 0.*mm; 
  si1BoxCenterZ = -100*mm + si1BoxSizeY;

  // create commands for interactive definition of the calorimeter
  si1Messenger = new CDSSDSi1DetectorMessenger(this);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi1DetectorConstruction::~CDSSDSi1DetectorConstruction(){
  if (si1Messenger !=NULL ) delete si1Messenger;
  if (nistman != NULL) delete nistman;
  if (detConstruction != NULL) delete detConstruction;
  if( si1Log != NULL) delete si1Log;
  
}

//////////////////////////////////////////////////////////////////
/// Wrap for the construction functions within the TOF
G4VPhysicalVolume* CDSSDSi1DetectorConstruction::Construct(G4LogicalVolume* motherLog) {
  return ConstructSi1(motherLog);
}

//////////////////////////////////////////////////////////////////
/// Constructs the Si1 volume detector elements
G4VPhysicalVolume* CDSSDSi1DetectorConstruction::ConstructSi1(G4LogicalVolume* motherLog) {
   
  G4VPhysicalVolume* si1Phys; 
  G4Box* si1Box;
  si1Box = new G4Box("si1Box",si1BoxSizeX,si1BoxSizeY,si1BoxSizeZ);  
  si1Log = new G4LogicalVolume(si1Box,nistman->FindOrBuildMaterial("G4_Si"),"si1Log");
  si1Phys = new G4PVPlacement(0, G4ThreeVector(si1BoxCenterX,si1BoxCenterY,si1BoxCenterZ),si1Log,"si1Phys",motherLog,false,0,true);

  return si1Phys;
}



