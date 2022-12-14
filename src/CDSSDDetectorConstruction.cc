#include "CDSSDDetectorConstruction.hh"
#include "CDSSDDetectorMessenger.hh"

#include "CDSSDSi1DetectorConstruction.hh"

#include "CDSSDSi1SD.hh"

#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "globals.hh"
#include "G4AssemblyVolume.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


//////////////////////////////////////////////////////////////////
/// Constructor: initialize all variables, materials and pointers
CDSSDDetectorConstruction::CDSSDDetectorConstruction()
  : si1SD(0), solidWorld(0), worldLog(0),  worldPhys(0), si1Det(0) {

  G4cout << "CDSSD Detector Construction" << G4endl;

  //initialize the G4NISTMaterial manager
  nistman = G4NistManager::Instance();

  //default values of half-length -> size of World (2x2x2 m3)
  worldSizeX = 1.*m;
  worldSizeY = 1.*m;
  worldSizeZ = 1.*m;
 
  //define default materials
  DefineMaterials();

 
  //Modular detector construction objects
  si1Det = new CDSSDSi1DetectorConstruction(this);

  // create commands for interactive definition of the detector
  detectorMessenger = new CDSSDDetectorMessenger(this);
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDDetectorConstruction::~CDSSDDetectorConstruction() {

  if(detectorMessenger != NULL) delete detectorMessenger;
 
}

//////////////////////////////////////////////////////////////////
/// GEANT4 mandatory method for the geometry implementation.

G4VPhysicalVolume* CDSSDDetectorConstruction::Construct() {

  return ConstructCDSSD();

}

////////////////////////////////////////////////////////////////
/// Constructs the CDSSD  geometry

G4VPhysicalVolume* CDSSDDetectorConstruction::ConstructCDSSD() {

  //--------------------------
  //World Volume
  //--------------------------

  //Geometrical definition of the world, half sizes
  SetWorldSizeX(1*m);
  SetWorldSizeY(1*m);
  SetWorldSizeZ(1*m);

  solidWorld = new G4Box("World",                //its name
			 worldSizeX,worldSizeY,worldSizeZ);  //its size

  worldLog = new G4LogicalVolume(solidWorld,     //its solid
				 nistman->FindOrBuildMaterial("G4_Galactic"),                 //its material
				 "World");                       //its name

  worldPhys = new G4PVPlacement(0,     //no rotation
				G4ThreeVector(),       //at (0,0,0)
				worldLog,              //its logical volume
				"World",               //its name
				0,                     //its mother  volume
				false,                 //no boolean operation
				0);                    //copy number

  
  //--------------------------
  // CDSSD volume
  //--------------------------
 
  si1Det->Construct(worldLog);
  

  

  return worldPhys;

}

////////////////////////////////////////////////////////////////
/// Sets the Sensitive Detectors 
void CDSSDDetectorConstruction::ConstructSDandField(){

  G4cout << "Setting the SD volumes" << G4endl;

  //The SD manager
  SDman = G4SDManager::GetSDMpointer();
  
  // Si1 volume sensitive detector
  G4String gasSDname = "si1SD";
  si1SD = new CDSSDGasSD(gasSDname);
  
  SDman->AddNewDetector(si1SD);
  SetSensitiveDetector(si1Det->GetLogicalVolume()->GetName(), si1SD);  

}


////////////////////////////////////////////////////////////////
/// Define the materials to be used
void CDSSDDetectorConstruction::DefineMaterials() {

  //
  // define materials
  //
  G4double density, pressure, temperature;
  G4int ncomponents, natoms;
  G4double fractionmass;

  /* How to set a GAS
  density	=0.0688*mg/cm3;
  pressure	=0.3*bar;
  temperature	=298.2*kelvin;
  G4Material* HeCF4300=
    new G4Material("HeCF4_300", density,ncomponents=3,kStateGas, temperature, pressure);
  HeCF4300->AddElement (He,natoms=98);
  HeCF4300->AddElement (C,natoms=2);
  HeCF4300->AddElement (F,natoms=8); */


  /* How to set Material from element
  G4Material* H2O =
    new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->SetChemicalFormula("H_2O");
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV); */

  /*How to set material from material */
  //  Peek chemical formula (C19H12O3)
  // C 114/150 = 76
  // H 12/150  = 8
  // O 24/150  = 16

  G4Material *Peek = new G4Material("Peek",   density = 1.31*g/cm3, ncomponents=3);
  Peek->AddMaterial(nistman->FindOrBuildMaterial("G4_C"), 0.76);
  Peek->AddMaterial(nistman->FindOrBuildMaterial("G4_H"),  0.08);
  Peek->AddMaterial(nistman->FindOrBuildMaterial("G4_O"), 0.16);

  defaultMaterial  = nistman->FindOrBuildMaterial("G4_Galactic");


}

