#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetTargetMaterial  (G4String);
    void SetChamberMaterial (G4String);
    void SetMaxStep         (G4double);

  private:
    // methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    G4String targetMaterial_;
    G4double targetThickness_;
    G4LogicalVolume* Target_L;
    //
    G4int              fNbOfChambers;   // number of tracking chambers (not implemented yet)
    G4LogicalVolume*   fLogicTarget;    // pointer to the logical Target
    G4LogicalVolume**  fLogicChamber;   // pointer to the logical Chamber
    G4Material*        fTargetMaterial; // pointer to the target  material
    G4UserLimits*      fStepLimit;      // pointer to user step limits
    DetectorMessenger* fMessenger;      // messenger

    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
};

#endif
