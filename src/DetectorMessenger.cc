#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
: G4UImessenger(),
  fDetectorConstruction(Det)
{
  fB2Directory = new G4UIdirectory("/B2/");
  fB2Directory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/B2/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fTargMatCmd = new G4UIcmdWithAString("/B2/det/setTargetMaterial",this);
  fTargMatCmd->SetGuidance("Select Material of the Target.");
  fTargMatCmd->SetParameterName("choice",false);
  fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/B2/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax",false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);
}


DetectorMessenger::~DetectorMessenger()
{
  delete fTargMatCmd;
  delete fStepMaxCmd;
  delete fB2Directory;
  delete fDetDirectory;
}


void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command==fTargMatCmd) {
    fDetectorConstruction->SetTargetMaterial(newValue); return;

  } else if (command==fStepMaxCmd) {
    fDetectorConstruction->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue)); return;

  }
}


