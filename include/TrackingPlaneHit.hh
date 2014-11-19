#ifndef TrackingPlaneHit_h
#define TrackingPlaneHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"


class TrackingPlaneHit : public G4VHit
{
  public:
    TrackingPlaneHit();
    TrackingPlaneHit(const TrackingPlaneHit&);
    virtual ~TrackingPlaneHit();

    // operators
    const TrackingPlaneHit& operator=(const TrackingPlaneHit&);
    G4int operator==(const TrackingPlaneHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetName     (G4String str)    { name_   = str; };
    void SetPDGID    (G4int i)         { pdgID_  = i; };
    void SetPlaneNum (G4int i)         { nplane_ = i; };
    void SetTime     (G4double d)      { time_   = d; };
    void SetPos      (G4ThreeVector v) { pos_    = v; };
    void SetMom      (G4ThreeVector v) { mom_    = v; };
    void SetMomMag   (G4double d)      { pmag_   = d; };

    // Get methods
    G4String      GetName()     const { return name_;   };
    G4int         GetPDGID()    const { return pdgID_;  };
    G4int         GetPlaneNum() const { return nplane_; };
    G4double      GetTime()     const { return time_;   };
    G4ThreeVector GetPos()      const { return pos_;    };
    G4ThreeVector GetMom()      const { return mom_;    };
    G4double      GetMomMag()   const { return pmag_;   };

  private:
    G4String      name_;
    G4int         pdgID_;
    G4int         nplane_;
    G4double      time_;
    G4ThreeVector pos_;
    G4ThreeVector mom_;
    G4double      pmag_;
};


typedef G4THitsCollection<TrackingPlaneHit> TrackingPlaneHitsCollection;

extern G4ThreadLocal G4Allocator<TrackingPlaneHit>* TrackingPlaneHitAllocator;


inline void* TrackingPlaneHit::operator new(size_t)
{
  if (!TrackingPlaneHitAllocator)
    TrackingPlaneHitAllocator = new G4Allocator<TrackingPlaneHit>;
  return (void *) TrackingPlaneHitAllocator->MallocSingle();
}


inline void TrackingPlaneHit::operator delete(void *hit)
{
  TrackingPlaneHitAllocator->FreeSingle((TrackingPlaneHit*) hit);
}

#endif
