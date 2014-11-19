#ifndef RootMessenger_hh
#define RootMessenger_hh 1

#include "globals.hh"
#include "G4UImessenger.hh"

class RootManager;
class G4UIcommand;
class G4UIcmdWithAString;


class RootMessenger : public G4UImessenger
{
  public:
    RootMessenger( RootManager* );
    virtual ~RootMessenger();
    virtual void SetNewValue( G4UIcommand*, G4String );

  private:
    RootManager*        rootMgr_;
    G4UIdirectory*      rootUIDir_;
    G4UIcmdWithAString* rootOutputDirCmd_;
    G4UIcmdWithAString* rootOutputFileCmd_;
};

#endif
