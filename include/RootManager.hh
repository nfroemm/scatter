#ifndef RootManager_hh
#define RootManager_hh 1

#include "globals.hh"
#include "G4ThreeVector.hh"

class RootMessenger;
class TFile;
class TTree;


class RootManager
{
  public:
    RootManager();
    virtual ~RootManager();

  public:
    // Methods for creating/saving root files (via RunAction)
    void SetOutputDir(G4String);
    void SetOutputFile(G4String);
    void Book();
    void Save();

  private:
    RootMessenger* rootMsgr_;
    G4String       dirname_;
    G4String       filename_;
    TFile*         rootfile_;
    TTree*         hitTree_;
    int pdgid_, nplane_; // hit info
    float t_, x_, y_, z_, xp_, yp_, dpp_, pmag_;

  public:
    // A method to fill the tree (via EventAction)
    void FillHitTree(
      G4int pdgid,
      G4int nplane,
      G4double time,
      G4ThreeVector pos,
      G4ThreeVector mom,
      G4double pmag
    );
};

#endif
