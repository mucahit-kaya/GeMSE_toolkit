////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// XENONnT assembled PMT bases
// Sample 2019-03-12

// Side cuboid blocks (together): 1179 g
// Top block: 692 g

// Materials
G4Element* N = nist->FindOrBuildElement("N");
G4Material* Cirlex = new G4Material("Cirlex", 1.43 * g / cm3, 4, kStateSolid);
Cirlex->AddElement(C, 22);
Cirlex->AddElement(H, 10);
Cirlex->AddElement(N, 2);
Cirlex->AddElement(O, 5);

G4Material* Cirlex_Air =
    new G4Material("Cirlex_Air", 0.786 * g / cm3, 2, kStateSolid);
Cirlex_Air->AddMaterial(Cirlex, 0.55);
Cirlex_Air->AddMaterial(air_mat, 0.45);

// Dimensions
G4double basesbrick_side = 121.5 * mm;
G4double basesbrickside_thick = 50. * mm;
G4double basesbrickside_top = 59. * mm;
G4double zPosblockSide = zPosCuShielding + zSizeCuShielding / 2. -
                         zSizeSampleChamber + basesbrick_side / 2.;
G4double zPosblockTop =
    zPosEndcap + heightEndcap / 2. + basesbrickside_top / 2.;

G4Box* bases_sidebrick1 =
    new G4Box("bases_sidebrick1", basesbrick_side / 2.,
              basesbrickside_thick / 2., basesbrick_side / 2.);
G4LogicalVolume* bases_sidebrick1_log = new G4LogicalVolume(
    bases_sidebrick1, Cirlex_Air, "bases_sidebrick1_log", 0, 0, 0);
new G4PVPlacement(
    0,
    G4ThreeVector(0., outerRadiusEndcap + 10. * mm + basesbrickside_thick / 2.,
                  zPosblockSide),
    bases_sidebrick1_log, "bases_sidebrick_1", expHall_log, false, 0);

G4Box* bases_sidebrick2 =
    new G4Box("bases_sidebrick2", basesbrickside_thick / 2.,
              basesbrick_side / 2., basesbrick_side / 2.);
G4LogicalVolume* bases_sidebrick2_log = new G4LogicalVolume(
    bases_sidebrick2, Cirlex_Air, "bases_sidebrick2_log", 0, 0, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-(outerRadiusEndcap + 10. * mm +
                                  basesbrickside_thick / 2.),
                                0., zPosblockSide),
                  bases_sidebrick2_log, "bases_sidebrick_2", expHall_log, false,
                  0);

G4Box* bases_topbrick =
    new G4Box("bases_topbrick", basesbrick_side / 2., basesbrick_side / 2.,
              basesbrickside_top / 2.);
G4LogicalVolume* bases_topbrick_log = new G4LogicalVolume(
    bases_topbrick, Cirlex_Air, "bases_topbrick_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., zPosblockTop), bases_topbrick_log,
                  "bases_topbrick", expHall_log, false, 0);

// Visualization attributes
G4VisAttributes* violet = new G4VisAttributes(G4Colour(0.5, 0.0, 1.0));
bases_sidebrick1_log->SetVisAttributes(violet);
bases_sidebrick2_log->SetVisAttributes(violet);
bases_topbrick_log->SetVisAttributes(violet);

// Output sample mass
const G4double pmtsbases_mass =
    bases_sidebrick1_log->GetMass(false, false) / g +
    bases_sidebrick2_log->GetMass(false, false) / g +
    bases_topbrick_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Sample mass: " << pmtsbases_mass << " g" << G4endl;
G4cout << "############################" << G4endl;
