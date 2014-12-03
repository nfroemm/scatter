#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
: G4UImessenger(),
  fDetectorConstruction(Det)
{
  fSimDirectory = new G4UIdirectory("/mySim/");
  fSimDirectory->SetGuidance("UI commands specific to this application");

  fTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mySim/setTargetThickness",this);
  fTargetThicknessCmd->SetGuidance("Set the thickness of the target");
  fTargetThicknessCmd->SetParameterName("thickness",false);
  fTargetThicknessCmd->SetUnitCategory("Length");
  fTargetThicknessCmd->AvailableForStates(G4State_Idle);

  fTargetMaterialCmd = new G4UIcmdWithAString("/mySim/setTargetMaterial",this);
  fTargetMaterialCmd->SetGuidance("Set the material of the target");
  fTargetMaterialCmd->SetParameterName("choice",false);
  fTargetMaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/mySim/stepMax",this);
  fStepMaxCmd->SetGuidance("Define the maximum step length");
  fStepMaxCmd->SetParameterName("stepMax",false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);
}


DetectorMessenger::~DetectorMessenger()
{
  delete fSimDirectory;
  delete fTargetThicknessCmd;
  delete fTargetMaterialCmd;
  delete fStepMaxCmd;
}


void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  // Set the target material
  if (command==fTargetMaterialCmd) {
    fDetectorConstruction->SetTargetMaterial(newValue);
    return;
  } 
  // Set the target thickness
  if (command==fTargetThicknessCmd) {
    fDetectorConstruction->SetTargetThickness(fTargetThicknessCmd->GetNewDoubleValue(newValue));
    return;
  }
  // Set the maximum step length
  if (command==fStepMaxCmd) {
    fDetectorConstruction->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
    return;
  }
}


