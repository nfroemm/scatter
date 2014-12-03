#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;


class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction*);
    virtual ~DetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*,G4String);
    
  private:
    DetectorConstruction*      fDetectorConstruction;
    G4UIdirectory*             fSimDirectory;
    G4UIcmdWithAString*        fTargetMaterialCmd;
    G4UIcmdWithADoubleAndUnit* fTargetThicknessCmd;
    G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
};

#endif
