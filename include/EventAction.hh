#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

class RootManager;


class EventAction : public G4UserEventAction
{
  public:
    EventAction(RootManager*);
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event*);
    virtual void    EndOfEventAction(const G4Event*);

  private:
    RootManager* rootMgr_;
};

#endif
