#include "RootMessenger.hh"
#include "RootManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"


RootMessenger::RootMessenger(RootManager* rootMgr)
: G4UImessenger(),
  rootMgr_(rootMgr),
  rootUIDir_(0),
  rootOutputDirCmd_(0),
  rootOutputFileCmd_(0)
{
  // Make a new user-interface directory
  rootUIDir_ = new G4UIdirectory("/ROOT/");
  rootUIDir_->SetGuidance("UI commands for controlling ROOT output.");

  // Create a command for setting output directory
  rootOutputDirCmd_ = new G4UIcmdWithAString("/ROOT/setOutputDir",this);
  rootOutputDirCmd_->SetGuidance("Set output directory.");
  rootOutputDirCmd_->SetParameterName("choice",false);
  rootOutputDirCmd_->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Create a command for setting file directory
  rootOutputFileCmd_ = new G4UIcmdWithAString("/ROOT/setOutputFile",this);
  rootOutputFileCmd_->SetGuidance("Set output file.");
  rootOutputFileCmd_->SetParameterName("choice",false);
  rootOutputFileCmd_->AvailableForStates(G4State_PreInit,G4State_Idle);
}


RootMessenger::~RootMessenger()
{
  delete rootUIDir_;
  delete rootOutputDirCmd_;
  delete rootOutputFileCmd_;
}


void RootMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
  if (cmd==rootOutputDirCmd_) {
    rootMgr_->SetOutputDir(newValue);
    return;

  } else if (cmd==rootOutputFileCmd_) {
    rootMgr_->SetOutputFile(newValue);
    return;

  }
}

