#include "CDSSDSi1GeantHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

G4Allocator<CDSSDSi1GeantHit>* CDSSDSi1GeantHitAllocator;

//////////////////////////////////////////////////////////////////
/// Constructor
CDSSDSi1GeantHit::CDSSDSi1GeantHit() {
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi1GeantHit::~CDSSDSi1GeantHit() {
}

//////////////////////////////////////////////////////////////////
/// Copy constructor
CDSSDSi1GeantHit::CDSSDSi1GeantHit(const CDSSDSi1GeantHit& right) : G4VHit() {
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
const CDSSDSi1GeantHit& CDSSDSi1GeantHit::operator=(const CDSSDSi1GeantHit& right){
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
G4int CDSSDSi1GeantHit::operator==(const CDSSDSi1GeantHit& right) const{
  return (this==&right) ? 1 : 0;
}

// //////////////////////////////////////////////////////////////////
// /// Draws the Hit. A clear red point on the Hit position
// void CDSSDSi1GeantHit::Draw(){
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
void CDSSDSi1GeantHit::Print(){

}
