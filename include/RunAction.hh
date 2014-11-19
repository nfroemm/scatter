#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"

class RootManager;


class RunAction : public G4UserRunAction
{
  public:
    RunAction(RootManager*);
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    RootManager* rootMgr_;
};

#endif
