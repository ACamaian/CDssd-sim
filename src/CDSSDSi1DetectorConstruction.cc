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
#include "G4PVReplica.hh"
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

  si1Rmin = 50 * mm;
  si1Rmax = 150 * mm;
  
  si1RminActive = 50 * mm;
  si1RmaxActive = 150 * mm;
  
  si1Thickness = 20 * um;
  si1AlThickness = 0.5 * um;
  
  DPhigap = 10*deg;
  DPhisi = 80 *deg ;
  
  si1NSlices = 4;
  
  si1PosZ = -100 * mm;

  // create commands for interactive definition of the calorimeter
  si1Messenger = new CDSSDSi1DetectorMessenger(this);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi1DetectorConstruction::~CDSSDSi1DetectorConstruction(){
  if (si1Messenger !=NULL ) delete si1Messenger;
  if (nistman != NULL) delete nistman;
  if (detConstruction != NULL) delete detConstruction;
  if (motherSi1_log != NULL) delete motherSi1_log;
  
}

//////////////////////////////////////////////////////////////////
/// Wrap for the construction functions within the TOF
G4VPhysicalVolume* CDSSDSi1DetectorConstruction::Construct(G4LogicalVolume* motherLog) {
  return ConstructSi1(motherLog);
}

//////////////////////////////////////////////////////////////////
/// Constructs the Si1 volume detector elements
G4VPhysicalVolume* CDSSDSi1DetectorConstruction::ConstructSi1(G4LogicalVolume* motherLog) {
          
    G4VSolid* motherSi1 = new G4Tubs("motherSi1", si1RminActive, si1RmaxActive, (si1Thickness+si1AlThickness)/2., 0., 360 *deg);
    motherSi1_log = new G4LogicalVolume(motherSi1, nistman->FindOrBuildMaterial("G4_Galactic"), "motherSi1_log", 0, 0, 0);
    G4VPhysicalVolume* motherSi1_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,si1PosZ-(si1Thickness+si1AlThickness)/2), motherSi1_log, "motherSi1_phys",  motherLog, false, 0, true);
    
    G4double DPhiSlice = 360*deg/si1NSlices;
        
     //a slice to be replicated
    auto sliceS  = new G4Tubs("Slice",si1RminActive, si1RmaxActive, (si1Thickness+si1AlThickness)/2., -DPhiSlice/2., DPhiSlice);
    auto sliceL  = new G4LogicalVolume(sliceS,nistman->FindOrBuildMaterial("G4_Galactic"),"SliceL"); 
    auto sliceP = new G4PVReplica("SliceP",sliceL, motherSi1_log, kPhi, si1NSlices, DPhiSlice, 0.); 

    //a slice is done by a gap + active volume (see QQQ1 mesitech)
    auto gapS = new G4Tubs("Gap",si1RminActive, si1RmaxActive, (si1Thickness+si1AlThickness)/2., -DPhiSlice/2., DPhigap);
    auto gapL = new G4LogicalVolume(gapS, nistman->FindOrBuildMaterial("G4_TEFLON"),"GapL"); 
    auto gapP = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), gapL, "GapP", sliceL, false, 0, true);
        
    auto siS = new G4Tubs("Si1", si1RminActive, si1RmaxActive, si1Thickness/2., -DPhiSlice/2. + DPhigap, DPhisi);
    Si1Active_log = new G4LogicalVolume(siS, nistman->FindOrBuildMaterial("G4_Si"), "Si1ActiveL"); 
    auto siP = new G4PVPlacement(0,G4ThreeVector(0.,0., -si1AlThickness/2.), Si1Active_log, "Si1P", sliceL, false, 0, true);
        
    //and and Al layer on the junction side
    auto alS = new G4Tubs("Al", si1RminActive, si1RmaxActive, si1AlThickness/2., -DPhiSlice/2. +DPhigap, DPhisi);
    auto alL = new G4LogicalVolume(alS, nistman->FindOrBuildMaterial("G4_Al"), "AlL"); 
    auto alP = new G4PVPlacement(0,G4ThreeVector(0.,0., +si1Thickness/2.), alL, "AlP", sliceL, false, 0, true);
    
    // dead frame 
    auto deadSin = new G4Tubs("deadIn", si1Rmin, si1RminActive, (si1Thickness+si1AlThickness)/2., 0., 360*deg);
    auto deadLin = new G4LogicalVolume(deadSin, nistman->FindOrBuildMaterial("G4_TEFLON"),"dead");
    auto deadPinP = new G4PVPlacement(0, G4ThreeVector(0.,0.,si1PosZ-(si1Thickness+si1AlThickness)/2.), deadLin, "dead",  motherLog, false, 0, true);
    
    auto deadSout = new G4Tubs("deadOut", si1RmaxActive, si1Rmax, (si1Thickness+si1AlThickness)/2., 0., 360*deg);
    auto deadLout = new G4LogicalVolume(deadSout, nistman->FindOrBuildMaterial("G4_TEFLON"),"dead");
    auto deadPout = new G4PVPlacement(0, G4ThreeVector(0.,0.,si1PosZ-(si1Thickness+si1AlThickness)/2.), deadLout, "dead",  motherLog, false, 0, true);
       
    
    return motherSi1_phys;
}



