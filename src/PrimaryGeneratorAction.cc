#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"

#include "G4RunManager.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  // Create a particle gun that shoots one particle at a time
  G4int nparticles = 1;
  particleGun_ = new G4ParticleGun(nparticles);

  // Set the default particle to mu+
  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
  particleGun_->SetParticleDefinition(particleDefinition);

  // Set the default momentum to P_magic, oriented exactly downstream
  particleGun_->SetParticleMomentum(3.09435*GeV);
  particleGun_->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

  // Modify the lifetime of the muon to guarantee there are no decay events
  particleGun_->GetParticleDefinition()->SetPDGLifeTime(1e18*ns);
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun_;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Here is a good way of determining how many particles will be shot total in the G4Run
  if (anEvent->GetEventID()==0) {
    G4int nparticles = G4RunManager::GetRunManager()->GetNumberOfEventsToBeProcessed();
    G4cout << "Number of particles to be fired: " << nparticles << G4endl;
  }

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class, we get the world volume
  // from G4LogicalVolumeStore.
  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  G4Box* worldBox = NULL;
  if (worldLV) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());

  if (worldBox) {
    worldZHalfLength = worldBox->GetZHalfLength();
  } else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }
  particleGun_->SetParticlePosition(G4ThreeVector(0,0,-worldZHalfLength));
  particleGun_->GeneratePrimaryVertex(anEvent);
}


