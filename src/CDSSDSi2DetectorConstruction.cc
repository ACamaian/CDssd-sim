#include "CDSSDSi2DetectorConstruction.hh"
#include "CDSSDDetectorConstruction.hh"
#include "CDSSDSi2DetectorMessenger.hh"
#include "CDSSDSi2SD.hh"

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
CDSSDSi2DetectorConstruction::
CDSSDSi2DetectorConstruction(CDSSDDetectorConstruction* det)
  :	detConstruction(det){

  G4cout << "CDSSD Si2 Detector Construction" << G4endl;

  //Intialize the Nistmanager
  nistman = G4NistManager::Instance();

  si2Rmin = 50 * mm;
  si2Rmax = 150 * mm;
  
  si2RminActive = 50 * mm;
  si2RmaxActive = 150 * mm;
  
  si2Thickness = 1500 * um;
  si2AlThickness = 0.5 * um;  
  
  DPhigap = 10*deg;
  DPhisi = 80 *deg ;
  
  si2NSlices = 4;
  
  si2PosZ = -100.040 * mm;

  // create commands for interactive definition of the calorimeter
  si2Messenger = new CDSSDSi2DetectorMessenger(this);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi2DetectorConstruction::~CDSSDSi2DetectorConstruction(){
  if (si2Messenger !=NULL ) delete si2Messenger;
  if (nistman != NULL) delete nistman;
  if (detConstruction != NULL) delete detConstruction;
  if (motherSi2_log != NULL) delete motherSi2_log;
  
}

//////////////////////////////////////////////////////////////////
/// Wrap for the construction functions within the TOF
G4VPhysicalVolume* CDSSDSi2DetectorConstruction::Construct(G4LogicalVolume* motherLog) {
  return ConstructSi2(motherLog);
}

//////////////////////////////////////////////////////////////////
/// Constructs the Si2 volume detector elements
G4VPhysicalVolume* CDSSDSi2DetectorConstruction::ConstructSi2(G4LogicalVolume* motherLog) {
      
    G4VSolid* motherSi2 = new G4Tubs("motherSi2", si2RminActive, si2RmaxActive, (si2Thickness+si2AlThickness)/2., 0., 360 *deg);
    motherSi2_log = new G4LogicalVolume(motherSi2, nistman->FindOrBuildMaterial("G4_Galactic"), "motherSi2_log", 0, 0, 0);
    G4VPhysicalVolume* motherSi2_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,si2PosZ-(si2Thickness+si2AlThickness)/2), motherSi2_log, "motherSi2_phys",  motherLog, false, 0, true);
    
    G4double DPhiSlice = 360*deg/si2NSlices;
        
     //a slice to be replicated
    auto sliceS  = new G4Tubs("Slice",si2RminActive, si2RmaxActive, (si2Thickness+si2AlThickness)/2., -DPhiSlice/2., DPhiSlice);
    auto sliceL  = new G4LogicalVolume(sliceS,nistman->FindOrBuildMaterial("G4_Galactic"),"SliceL"); 
    auto sliceP = new G4PVReplica("SliceP",sliceL, motherSi2_log, kPhi, si2NSlices, DPhiSlice, 0.); 

    //a slice is done by a gap + active volume (see QQQ1 mesitech)
    auto gapS = new G4Tubs("Gap",si2RminActive, si2RmaxActive, (si2Thickness+si2AlThickness)/2., -DPhiSlice/2., DPhigap);
    auto gapL = new G4LogicalVolume(gapS, nistman->FindOrBuildMaterial("G4_TEFLON"),"GapL"); 
    auto gapP = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), gapL, "GapP", sliceL, false, 0, true);
    
    auto siS = new G4Tubs("Si2", si2RminActive, si2RmaxActive, si2Thickness/2., -DPhiSlice/2. + DPhigap, DPhisi);
    Si2Active_log = new G4LogicalVolume(siS, nistman->FindOrBuildMaterial("G4_Si"), "Si2ActiveL"); 
    auto siP = new G4PVPlacement(0,G4ThreeVector(0.,0., -si2AlThickness/2.), Si2Active_log, "Si2P", sliceL, false, 0, true);
        
     //and and Al layer on the junction side
    auto alS = new G4Tubs("Al", si2RminActive, si2RmaxActive, si2AlThickness/2., -DPhiSlice/2. +DPhigap, DPhisi);
    auto alL = new G4LogicalVolume(alS, nistman->FindOrBuildMaterial("G4_Al"), "AlL"); 
    auto alP = new G4PVPlacement(0,G4ThreeVector(0.,0., +si2Thickness/2.), alL, "AlP", sliceL, false, 0, true);
    
    //dead frame 
    auto deadSin = new G4Tubs("deadIn", si2Rmin, si2RminActive, (si2Thickness+si2AlThickness)/2., 0., 360*deg);
    auto deadLin = new G4LogicalVolume(deadSin, nistman->FindOrBuildMaterial("G4_TEFLON"),"dead");
    auto deadPinP = new G4PVPlacement(0, G4ThreeVector(0.,0.,si2PosZ-(si2Thickness+si2AlThickness)/2), deadLin, "dead",  motherLog, false, 0, true);
    
    auto deadSout = new G4Tubs("deadOut", si2RmaxActive, si2Rmax, (si2Thickness+si2AlThickness)/2., 0., 360*deg);
    auto deadLout = new G4LogicalVolume(deadSout, nistman->FindOrBuildMaterial("G4_TEFLON"),"dead");
    auto deadPout = new G4PVPlacement(0, G4ThreeVector(0.,0.,si2PosZ-(si2Thickness+si2AlThickness)/2), deadLout, "dead",  motherLog, false, 0, true);
    
    return motherSi2_phys;
}



