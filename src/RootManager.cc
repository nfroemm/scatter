#include "RootManager.hh"
#include "RootMessenger.hh"
#include <TFile.h>
#include <TTree.h>

#include "globals.hh"


RootManager::RootManager()
: rootMsgr_(0),
  dirname_(""),
  filename_("x.root"),
  rootfile_(0),
  hitTree_(0),
  pdgid_(-999),
  nplane_(-999),
  t_(-999.),
  x_(-999.),
  y_(-999.),
  z_(-999.),
  xp_(-999.),
  yp_(-999.),
  dpp_(-999.),
  pmag_(-999.)
{
  rootMsgr_ = new RootMessenger(this);
}


RootManager::~RootManager()
{
  if (rootfile_) delete rootfile_;
  delete rootMsgr_;
}


void RootManager::SetOutputDir(G4String str)
{ dirname_ = str; }


void RootManager::SetOutputFile(G4String str)
{ filename_ = str; }


void RootManager::Book()
{
  // std::stringstream ss;
  // ss << dirname_ << filename_;

  // Create a new ROOT file each run
  rootfile_ = new TFile(filename_,"RECREATE");
  if (!rootfile_) {
    G4cout << "PROBLEM CREATING ROOT FILE" << G4endl;
    return;
  }

  // Tracking-plane hits tree
  hitTree_ = new TTree("TrackingPlaneHits","TrackingPlaneHits");
    hitTree_->Branch("pdgid",  &pdgid_,  "pdgid/I");
    hitTree_->Branch("nplane", &nplane_, "nplane/I");
    hitTree_->Branch("t",      &t_,      "t/F"  );
    hitTree_->Branch("x",      &x_,      "x/F"  );
    hitTree_->Branch("xp",     &xp_,     "xp/F" );
    hitTree_->Branch("y",      &y_,      "y/F"  );
    hitTree_->Branch("yp",     &yp_,     "yp/F" );
    hitTree_->Branch("z",      &z_,      "z/F"  );
    hitTree_->Branch("dpp",    &dpp_,    "dpp/F");
    hitTree_->Branch("pmag",   &pmag_,   "pmag/F");
}


void RootManager::Save()
{
  if (rootfile_) {
    rootfile_->Write();
    rootfile_->Close();
    G4cout << "\n Writing ROOT ouput to \"" << filename_ << "\"\n\n";
  }
}


void RootManager::FillHitTree(
  G4int pdgid,
  G4int nplane,
  G4double time,
  G4ThreeVector pos,
  G4ThreeVector mom,
  G4double pmag)
{
  // Convert GEANT to ROOT
  pdgid_  = pdgid; 
  nplane_ = nplane; 
  t_      = float(time);
  x_      = float(pos.x());
  y_      = float(pos.y());
  z_      = float(pos.z());
  xp_     = float(mom.x());
  yp_     = float(mom.y());
  dpp_    = float(mom.z());
  pmag_   = float(pmag);

  // Fill the tree
  if (hitTree_) hitTree_->Fill();
}
