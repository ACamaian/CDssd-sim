#include "CDSSDSi2GeantHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<CDSSDSi2GeantHit>* CDSSDSi2GeantHitAllocator = nullptr;



//////////////////////////////////////////////////////////////////

G4bool CDSSDSi2GeantHit::operator==(const CDSSDSi2GeantHit& right) const
{
  return ( this == &right ) ? true : false;
}


//////////////////////////////////////////////////////////////////
/// Prints full information about the calGeantHit
void CDSSDSi2GeantHit::Print(){

}


void CDSSDSi2GeantHit::Reset(){
    
    trackID = -1;          ///< ID for each track
    parentID = -1;         ///< ID for the parent track
    edep = 0;             ///< Energy deposited
    particleCharge = -1;   ///< Charge of the particle
    particleMass = -1;     ///< Mass of the particle
    particleID = -1;       ///< Particle ID according to the GDP-coding
    pos = {0,0,0};          ///< Position of the hit in absolute coordinates
    detName = "";          ///< Detector name where energy is deposited
    detID = -1;            ///< Detector ID
    islice = -1;
    
}
