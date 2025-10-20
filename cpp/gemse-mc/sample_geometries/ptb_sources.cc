////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// Assembly for the calibration sources setup
// Sample 2021-05-26

// Point-like cylindrical calibration sources on top of a holder system
// provided by Rugard Dresler (PSI)
// Standard dimensions of point sources by PTB:
// https://www.ptb.de/cms/en/ptb/fachabteilungen/abt6/fb-61/611-unit-of-activity/
//   delivery-of-activity-standards/activity-standards-in-the-form-of-solid-sources.html

// Holders from CAD STL files
// Source as simply tube embeded in polyethylene

// Dimensions
G4double dSourceThickness = 1.*mm;
G4double dSourceDiameter = 5*mm;
G4double dContainerThickness = 1.*mm;
G4double dContainerDiameter = 24*mm;
G4double zPosSource = 113.8*mm
   + zPosEndcap + heightEndcap/2.;

// Materials
G4Material* aluminium_mat = nist->FindOrBuildMaterial("G4_Al");
G4Material* ps_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

// Sample position and rotation
G4RotationMatrix rmr;
rmr.rotateX(180.*deg);
rmr.rotateZ(0.*deg);
G4ThreeVector sample_pos = G4ThreeVector(0, 0, zPosSource + 1.*mm);
// Just because of the coordinates in the STL file

G4LogicalVolume *holder_logical;

// Import holder
auto holder_mesh = CADMesh::TessellatedMesh::FromSTL
   ("sample_geometries/Holders_assembly_reduced.stl");
holder_mesh->SetScale(10.0); // Default is 1, corresponding to mm in Geant4
auto holder_solid = holder_mesh->GetSolid();
holder_logical = new G4LogicalVolume(holder_solid, aluminium_mat,
                                     "source_holder_logical", 0, 0, 0);
//new G4PVPlacement(G4Transform3D(rmr, sample_pos), holder_logical,
//                  "source_holder", expHall_log, false, 0);

// Calibration source
G4Tubs* container_tube = new G4Tubs ("container_tube", 0., dContainerDiameter/2.,
                                   dContainerThickness/2., 0., 360.*deg);
G4Tubs* ps_tube = new G4Tubs ("ps_tube", 0., dSourceDiameter/2.,
                              dSourceThickness/2., 0., 360.*deg);

G4LogicalVolume* container_log = new G4LogicalVolume(container_tube, ps_mat, "container_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., zPosSource+dContainerThickness/2.),
                  container_log, "source_container", expHall_log, false, 0);

G4LogicalVolume* ps_log = new G4LogicalVolume(ps_tube, ps_mat, "ps_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., 0),
                  ps_log, "calibration_source", container_log, false, 0);

// Visualization G4VisAttributes
G4VisAttributes* violet = new G4VisAttributes(G4Colour(0.5,0.0,1.0));
G4VisAttributes* lightblue = new G4VisAttributes(G4Colour(0.0,0.5,1.0));
holder_logical->SetVisAttributes(grey);
container_log->SetVisAttributes(lightblue);
ps_log->SetVisAttributes(violet);
