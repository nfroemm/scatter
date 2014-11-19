#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "RootManager.hh"


ActionInitialization::ActionInitialization()
: G4VUserActionInitialization(),
  rootMgr_(0)
{
  rootMgr_ = new RootManager();
}


ActionInitialization::~ActionInitialization()
{
  delete rootMgr_;
}


void ActionInitialization::BuildForMaster() const
{
  // Parallelized
  SetUserAction(new RunAction(rootMgr_));
}


void ActionInitialization::Build() const
{
  // Sequential mode (non-parallelized) and worker threads (parallelized)
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new RunAction(rootMgr_));
  SetUserAction(new EventAction(rootMgr_));
}  


