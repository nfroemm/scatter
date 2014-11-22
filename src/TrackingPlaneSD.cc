#include "TrackingPlaneSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4SystemOfUnits.hh"
#include <cmath>


TrackingPlaneSD::TrackingPlaneSD(const G4String& name, const G4String& hitsCollectionName) 
: G4VSensitiveDetector(name),
  fHitsCollection(NULL),
  verbosity(0)
{
  collectionName.insert(hitsCollectionName);
}


TrackingPlaneSD::~TrackingPlaneSD() 
{}


void TrackingPlaneSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection = new TrackingPlaneHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}


G4bool TrackingPlaneSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // Only process "primary" particles
  G4int trackID = aStep->GetTrack()->GetTrackID();
  if (trackID!=1) return false;

  // Create the new hit
  TrackingPlaneHit* newHit = new TrackingPlaneHit();

  // Get hit information
  G4String      name   = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4int         pdgID  = aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
  G4int         nplane = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  G4double      time   = aStep->GetPostStepPoint()->GetGlobalTime();
  G4ThreeVector pos    = aStep->GetPostStepPoint()->GetPosition();
  G4ThreeVector mom    = aStep->GetPostStepPoint()->GetMomentum();
  G4double      pmag   = mom.mag();

  // Convert momentum to beam-optical
  G4double xp, yp, dpp;
  if ( (name=="mu+") || (name=="mu-") ) {
    xp = mom.x()/(3094.349530048523*MeV);
    yp = mom.y()/(3094.349530048523*MeV);
  } else {
    G4ThreeVector phat = mom/pmag;
    xp = atan2( phat.x(),phat.z() );
    yp = asin( phat.y() );
  }
  dpp = (pmag-3094.349530048523*MeV)/(3094.349530048523*MeV);
  mom = G4ThreeVector(xp,yp,dpp);

  // Add information to hit
  newHit->SetName( name );
  newHit->SetPDGID( pdgID );
  newHit->SetPlaneNum( nplane );
  newHit->SetTime( time );
  newHit->SetPos( pos );
  newHit->SetMom( mom );
  newHit->SetMomMag( pmag );

  // Add hit to the collection
  fHitsCollection->insert( newHit );
  return true;
}


void TrackingPlaneSD::EndOfEvent(G4HCofThisEvent*)
{
  G4int nhits = fHitsCollection->entries();
  if (nhits>0) {
    if (verbosity>0) {
      G4cout << "\nTRACKING-PLANE HITS: " << nhits << "\n\n";
      G4int maxprint= std::min(nhits,25);
      for (G4int n=0; n!=maxprint; ++n) (*fHitsCollection)[n]->Print();
    }
  }
}


