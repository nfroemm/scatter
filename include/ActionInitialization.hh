#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class RootManager;


class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    RootManager* rootMgr_;
};

#endif
