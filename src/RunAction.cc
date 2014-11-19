#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "RootManager.hh"


RunAction::RunAction(RootManager* rootMgr)
: G4UserRunAction(),
  rootMgr_(rootMgr)
{ 
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
}


RunAction::~RunAction()
{}


void RunAction::BeginOfRunAction(const G4Run*)
{ 
  // Create a new ROOT file and setup tracking-plane hit tree
  rootMgr_->Book();

  // Inform the runManager to save random number seed?
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}


void RunAction::EndOfRunAction(const G4Run*)
{
  // Save the ROOT file at the end of the run
  rootMgr_->Save();
}


