#include "CDSSDSi2GeantHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

G4Allocator<CDSSDSi2GeantHit>* CDSSDSi2GeantHitAllocator;

//////////////////////////////////////////////////////////////////
/// Constructor
CDSSDSi2GeantHit::CDSSDSi2GeantHit() {
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi2GeantHit::~CDSSDSi2GeantHit() {
}

//////////////////////////////////////////////////////////////////
/// Copy constructor
CDSSDSi2GeantHit::CDSSDSi2GeantHit(const CDSSDSi2GeantHit& right) : G4VHit() {
  edep = right.edep;
  // particleCharge = right.particleCharge;
  // particleMass = right.particleMass;
  // particleID = right.particleID;
  // prePos = right.prePos;
  // postPos = right.postPos;
  // detName = right.detName;
  // detID = right.detID;
  // preToF = right.preToF;
  // postToF = right.postToF;
  // stepLength = right.stepLength;
  // stepEnergy = right.stepEnergy;
}

//////////////////////////////////////////////////////////////////
/// Operator =
const CDSSDSi2GeantHit& CDSSDSi2GeantHit::operator=(const CDSSDSi2GeantHit& right){
  edep = right.edep;
  // particleCharge = right.particleCharge;
  // particleMass = right.particleMass;
  // particleID = right.particleID;
  // prePos = right.prePos;
  // postPos = right.postPos;
  // detName = right.detName;
  // detID = right.detID;
  // preToF = right.preToF;
  // postToF = right.postToF;
  // stepLength = right.stepLength;
  // stepEnergy = right.stepEnergy;

  return *this;
}

//////////////////////////////////////////////////////////////////
/// Operator ==
G4int CDSSDSi2GeantHit::operator==(const CDSSDSi2GeantHit& right) const{
  return (this==&right) ? 1 : 0;
}

// //////////////////////////////////////////////////////////////////
// /// Draws the Hit. A clear red point on the Hit position
// void CDSSDSi2GeantHit::Draw(){
//   G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
//   if(pVVisManager) {
//     G4Circle circle(prePos);
//     circle.SetScreenSize(4);
//     circle.SetFillStyle(G4Circle::filled);
//     G4Colour colour(1.,0.,0.);
//     G4VisAttributes attribs(colour);
//     circle.SetVisAttributes(attribs);
//     pVVisManager->Draw(circle);
//   }
// }

//////////////////////////////////////////////////////////////////
/// Prints full information about the calGeantHit
void CDSSDSi2GeantHit::Print(){

}
