#include "TrackingPlaneHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4SystemOfUnits.hh"

#include <iomanip>


G4ThreadLocal G4Allocator<TrackingPlaneHit>* TrackingPlaneHitAllocator=0;


TrackingPlaneHit::TrackingPlaneHit()
: G4VHit(),
  name_(""),
  pdgID_(-999),
  nplane_(-1),
  time_(-1.),
  pos_(G4ThreeVector(-999.,-999.,-999.)),
  mom_(G4ThreeVector(-999.,-999.,-999.)),
  pmag_(-1.)
{}


TrackingPlaneHit::~TrackingPlaneHit()
{}


TrackingPlaneHit::TrackingPlaneHit(const TrackingPlaneHit& right)
  : G4VHit()
{
  name_    = right.name_;
  pdgID_   = right.pdgID_;
  nplane_  = right.nplane_;
  time_    = right.time_;
  pos_     = right.pos_;
  mom_     = right.mom_;
  pmag_    = right.pmag_;
}


const TrackingPlaneHit& TrackingPlaneHit::operator=(const TrackingPlaneHit& right)
{
  name_    = right.name_;
  pdgID_   = right.pdgID_;
  nplane_  = right.nplane_;
  time_    = right.time_;
  pos_     = right.pos_;
  mom_     = right.mom_;
  pmag_    = right.pmag_;

  return *this;
}


G4int TrackingPlaneHit::operator==(const TrackingPlaneHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}


void TrackingPlaneHit::Draw()
{}


void TrackingPlaneHit::Print()
{
#if 1
  G4cout << G4endl
    << "------------------"   << G4endl
    << "TRACKING-PLANE HIT"   << G4endl
    << "------------------"   << G4endl
    << "   name: " << name_   << G4endl
    << "  pdgID: " << pdgID_  << G4endl
    << " nplane: " << nplane_ << G4endl
    << "   time: " << time_/ns  << " ns"  << G4endl
    << "    pos: " << pos_/mm   << " mm"  << G4endl
    << "    mom: " << mom_/MeV  << " MeV" << G4endl
    << "   pmag: " << pmag_/MeV << " MeV" << G4endl
    << G4endl;
#endif
}


