////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// Banana screened for posterity
// Sample 2021-05-21

// One banana of exactly 265.15 g (right before scanning)
// Volume defined by the STL fine of the sample scan
// Remember copy the STL in the right folder! They aren't uploaded to GitHub

// Materials
// Let's figure out a decent banana composition,
// using https://doi.org/10.1093/fqsafe/fyy019 as a reference
// 1. The sum of all minerals, among which our targeted K, is 408.15mg/100g
// 2. Provided that we have H, O, C, the rest of the composition can be approximated to
//    water (74.91g/100g) + sugars&fibre (22.84g/100g).
//    Let's add these up so that they make 100g - 408.15 mg
G4Material *Water = new G4Material("Water", 1.*g/cm3, 2, kStateLiquid);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);
G4Material *Fructose = new G4Material("Fructose", 1.69*g/cm3, 3, kStateSolid);
  Fructose->AddElement(C, 6);
  Fructose->AddElement(H, 12);
  Fructose->AddElement(O, 6);
G4Element* Mg = nist->FindOrBuildElement("Mg");
G4Element* P = nist->FindOrBuildElement("P");
G4Element* K = nist->FindOrBuildElement("K");
G4Element* Na = nist->FindOrBuildElement("Na");
G4Element* Zn = nist->FindOrBuildElement("Zn");

G4Material *banana_mat = new G4Material("Banana_mat", 0.954*g/cm3, 7, kStateSolid);
  banana_mat->AddMaterial(Water, 0.7491/(0.2284+0.7491)*(1 - 0.0040815));
  banana_mat->AddMaterial(Fructose, 0.2284/(0.2284+0.7491)*(1 - 0.0040815));
  banana_mat->AddElement(Mg, 0.00027);
  banana_mat->AddElement(P, 0.00022);
  banana_mat->AddElement(K, 0.00358);
  banana_mat->AddElement(Na, 0.00001);
  banana_mat->AddElement(Zn, 0.0000015);

// Sample position
// The coordinate system of the banana scan and holder CAD were previously matched
// with Inventor, therefore only one rotation matrix and position vector are needed
G4RotationMatrix rmr;
rmr.rotateX(0);
rmr.rotateZ(45.*deg);
G4ThreeVector sample_pos = G4ThreeVector(0, 0, 19.75*mm);

G4LogicalVolume *holder_logical;
G4LogicalVolume *banana_logical;

// Import holder
auto holder_mesh = CADMesh::TessellatedMesh::FromSTL
   ("sample_geometries/bananaholder_banana_down_ASCI_holder.stl");
holder_mesh->SetScale(10.0); // Default is 1, corresponding to mm in Geant4
holder_mesh->SetOffset(sample_pos);
auto holder_solid = holder_mesh->GetSolid();

holder_logical = new G4LogicalVolume(holder_solid, Teflon,
                                     "holder_logical", 0, 0, 0);
new G4PVPlacement(G4Transform3D(rmr, sample_pos), holder_logical,
                  "banana_holder", expHall_log, false, 0);

// Import banana
auto banana_mesh = CADMesh::TessellatedMesh::FromSTL
   ("sample_geometries/bananaholder_banana_down_ASCI_banana.stl");
banana_mesh->SetScale(10.0);
banana_mesh->SetOffset(sample_pos);
auto banana_solid = banana_mesh->GetSolid();

banana_logical = new G4LogicalVolume(banana_solid, banana_mat,
                                     "banana_logical", 0, 0, 0);
new G4PVPlacement(G4Transform3D(rmr, sample_pos), banana_logical,
                  "banana", expHall_log, false, 0);

// Filling meshes with tetrahedra for navigation speedup
//auto mesh = CADMesh::TetrahedralMesh::FromSTL
//   ("sample_geometries/bananaholder_banana_down_ASCI_banana.stl");
//mesh->SetOffset(sample_pos);
//auto assembly = mesh->GetAssembly();
//auto position = G4ThreeVector();
//auto rotation = new G4RotationMatrix();
//assembly->MakeImprint(expHall_log, position, rotation);

// Print sample mass
const G4double holder_mass = holder_logical->GetMass(false, false)/g;
const G4double banana_mass = banana_logical->GetMass(false, false)/g;

G4cout << "\n############################" << G4endl;
G4cout << "Holder mass: " << holder_mass << " g" << G4endl;
G4cout << "Banana mass: " << banana_mass << " g" << G4endl;
G4cout << "############################\n" << G4endl;

// Visualization G4VisAttributes
G4VisAttributes* white = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
G4VisAttributes* yellow = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
holder_logical->SetVisAttributes(white);
banana_logical->SetVisAttributes(yellow);
