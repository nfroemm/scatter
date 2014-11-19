#ifndef TrackingPlaneSD_h
#define TrackingPlaneSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackingPlaneHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;


class TrackingPlaneSD : public G4VSensitiveDetector
{
  public:
    TrackingPlaneSD(const G4String& name, const G4String& hitsCollectionName);
    virtual ~TrackingPlaneSD();
  
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    TrackingPlaneHitsCollection* fHitsCollection;
    G4int verbosity;
};

#endif
