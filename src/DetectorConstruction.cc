#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TrackingPlaneSD.hh"

#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "G4UserLimits.hh"

 
G4ThreadLocal G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), 
  targetMaterial_("G4_Cu"),
//targetMaterial_("G4_Al"),
//targetMaterial_("G4_GRAPHITE"),
  targetThickness_(20.*mm),
  Target_L(0),
  fNbOfChambers(0),
  fLogicChamber(0), 
  fTargetMaterial(0),
  fStepLimit(0)
{
  fNbOfChambers = 1;
  fLogicChamber = new G4LogicalVolume*[fNbOfChambers];
  fMessenger = new DetectorMessenger(this);
}

 
DetectorConstruction::~DetectorConstruction()
{
  delete [] fLogicChamber; 
  delete fStepLimit;
  delete fMessenger;
}

 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}


void DetectorConstruction::DefineMaterials()
{
  // Set the default target material
  G4NistManager* nistManager = G4NistManager::Instance();

  // Here are some common materials the target can be made out of
  nistManager->FindOrBuildMaterial("G4_GRAPHITE");
  nistManager->FindOrBuildMaterial("G4_Al");
  nistManager->FindOrBuildMaterial("G4_Cu");

  // The quad/kicker standoffs are made out of "macor", a machinable glass ceramic (Source: 
  // http://www.azom.com/details.asp?ArticleID=1459 (accessed Mon 21 Apr 2014)).
  G4Material* Macor = new G4Material("Macor", 2.52*g/cm3, 6);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_SILICON_DIOXIDE"),46.*perCent);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_ALUMINUM_OXIDE"), 16.*perCent);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_POTASSIUM_OXIDE"),10.*perCent);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE"),17.*perCent);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_B"),4.4*perCent);
    Macor->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"),6.6*perCent);

  // Set the target material
  fTargetMaterial = nistManager->FindOrBuildMaterial( targetMaterial_ );

  // Print the materials list
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // World
  G4Box*             worldS  = new G4Box("world", 0.5*m, 0.5*m, 0.5*m);
  G4LogicalVolume*   worldLV = new G4LogicalVolume(worldS, G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"), "World");
  G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, true);

  // Target
  G4double t_hx = 0.5*worldS->GetXHalfLength();
  G4double t_hy = 0.5*worldS->GetYHalfLength();
  G4double t_hz = targetThickness_/2.;
  G4Box* Target_S = new G4Box("Target", t_hx, t_hy, t_hz);
         Target_L = new G4LogicalVolume(Target_S, fTargetMaterial, "Target", 0, 0, 0, true);
                    new G4PVPlacement(0, G4ThreeVector(), Target_L, "Target", worldLV, false, 0, true);

  // Tracking Plane
  G4double tp_hx = Target_S->GetXHalfLength();
  G4double tp_hy = Target_S->GetYHalfLength();
  G4double tp_hz = 0.5*micrometer;
  G4Box*           TrackingPlane_S = new G4Box("TrackingPlane", tp_hx, tp_hy, tp_hz);
  G4LogicalVolume* TrackingPlane_L = new G4LogicalVolume(TrackingPlane_S, G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"), "TrackingPlane", 0, 0, 0, true);
                                     new G4PVPlacement(0, G4ThreeVector(0,0,(t_hz+tp_hz)), TrackingPlane_L, "TrackingPlane", worldLV, false, 0, true);

//G4VisAttributes* targetVisAtt;
//if () {
//}

  // Required by GEANT
  return worldPV;
}

 
void DetectorConstruction::ConstructSDandField()
{
  trackingPlaneSD_ = new TrackingPlaneSD("TrackingPlaneSD","TrackingPlaneHitsCollection");
  SetSensitiveDetector("TrackingPlane", trackingPlaneSD_, true);
}

 
void DetectorConstruction::SetTargetMaterial(G4String materialName)
{
  // Get a pointer to the desired target material
  G4Material* newMaterial = G4NistManager::Instance()->FindOrBuildMaterial( materialName );
  // Check to make sure the desired target material is a valid G4Material
  if (newMaterial) {
    // Set the target material to the new target material
    targetMaterial_ = materialName;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4cout << "--> Target material is now: " << Target_L->GetMaterial()->GetName() << G4endl;
  } else {
    // Oops, the desired target material is invalid!
    G4cout << "--> ERROR: DetectorConstruction::SetTargetMaterial() : " << materialName << " not found!\n";
    throw;
  }
}


void DetectorConstruction::SetTargetThickness(G4double newThickness)
{
  // Check to make sure the thickness is valid
  if (newThickness>0.) {
    // Set the target thickness to the new thickness
    targetThickness_ = newThickness;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
    G4cout << "--> Target thickness is now: " << targetThickness_/mm << " mm"  << G4endl;
  } else {
    // Oops, the desired target thickness is invalid!
    G4cout << "--> ERROR: DetectorConstruction::SetTargetThickness() : " << newThickness << " <= 0!\n";
    throw;
  }
}
 

void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ( (fStepLimit) && (maxStep>0.) ) fStepLimit->SetMaxAllowedStep(maxStep);
}


