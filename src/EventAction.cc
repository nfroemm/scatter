#include "EventAction.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"



#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"


#include "TrackingPlaneHit.hh"

#include "RootManager.hh"


EventAction::EventAction(RootManager* rootMgr)
: G4UserEventAction(),
  rootMgr_(rootMgr)
{}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event*)
{}


void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get the tracking-plane hits collection ID
  G4int hcid = G4SDManager::GetSDMpointer()->GetCollectionID("TrackingPlaneHitsCollection");
  if (hcid<0) return;

  // Get the hits from the collection
  TrackingPlaneHitsCollection* hc = static_cast<TrackingPlaneHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcid));
  if (!hc) return;

  // Loop over the hits collection
  for (G4int n=0; n!=hc->entries(); ++n)
  {
    // Get the hit
    TrackingPlaneHit* hit = (*hc)[n];

    // Define some helper variables
    G4int pdgID, nplane;
    G4double time, pmag;
    G4ThreeVector pos, mom;

    // Get info from the hit
    pdgID  = hit->GetPDGID();
    nplane = hit->GetPlaneNum();
    time   = hit->GetTime();
    pos    = hit->GetPos();
    mom    = hit->GetMom();
    pmag   = hit->GetMomMag();

    // Fill the ROOT tree
    rootMgr_->FillHitTree( pdgID, nplane, time, pos, mom, pmag );

#if 0
    // Periodic printing
    G4int eventID = event->GetEventID();
    G4int maxprint = 25;
    if ( eventID<maxprint || eventID%100==0 ) {
      G4cout << ">>> EVENT " << eventID+1;
      hit->Print();
    } else if (eventID==maxprint) {
      G4cout << "-----> SNIP <-----\n\n\n";
    }
#endif

  }
}  


