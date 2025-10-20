////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// XENONnT PTFE for the PMT tri-lobed holders
// Sample 2019-04-10

// PTFE cylinders with 110 mm diameter
// - 12 x 60 mm height
// - 1 x 150 mm height
// Total screened mass: 18.189 kg

// Dimensions
G4double holders_diameter = 110. * mm;
G4double holders_side_height = 60. * mm;
G4double holders_top_height = 150. * mm;
G4double zPosTop = zPosEndcap + heightEndcap / 2. + holders_top_height / 2.;
G4double zPosSideLow = zPosCuShielding + zSizeCuShielding / 2. -
                       zSizeSampleChamber + holders_diameter / 2.;
G4double zPosSideMed = zPosSideLow + 89. * mm;
G4double zPosSideTop = zPosSideMed + 89. * mm;
G4double xShift = xSizeSampleChamber / 2. - holders_side_height / 2.;
G4double yShift = xSizeSampleChamber / 2. - holders_diameter / 2.;

// Placement top cylinder
G4Tubs* holder_top = new G4Tubs("holder_top", 0., holders_diameter / 2.,
                                holders_top_height / 2., 0. * deg, 360. * deg);
G4LogicalVolume* holder_top_log =
    new G4LogicalVolume(holder_top, Teflon, "holder_top_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., zPosTop), holder_top_log,
                  "PTFE_holder_top", expHall_log, false, 0);

// Placement side cylinders
G4Tubs* holders_side =
    new G4Tubs("holders_side", 0., holders_diameter / 2.,
               holders_side_height / 2., 0. * deg, 360. * deg);
G4LogicalVolume* holders_side_log =
    new G4LogicalVolume(holders_side, Teflon, "holders_side_log", 0, 0, 0);

G4RotationMatrix rm_holders;
rm_holders.rotateX(90. * deg);

G4ThreeVector sideholder_pos = G4ThreeVector(0, xShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side00", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(0, -xShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side01", expHall_log, false, 0);

rm_holders.rotateZ(90. * deg);

sideholder_pos = G4ThreeVector(xShift, yShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side02", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(xShift, -yShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side03", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(-xShift, yShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side04", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(-xShift, -yShift, zPosSideLow);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side05", expHall_log, false, 0);

sideholder_pos = G4ThreeVector(xShift, 0., zPosSideMed);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side06", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(-xShift, 0., zPosSideMed);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side07", expHall_log, false, 0);

sideholder_pos = G4ThreeVector(xShift, yShift, zPosSideTop);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side08", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(xShift, -yShift, zPosSideTop);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side09", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(-xShift, yShift, zPosSideTop);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side10", expHall_log, false, 0);
sideholder_pos = G4ThreeVector(-xShift, -yShift, zPosSideTop);
new G4PVPlacement(G4Transform3D(rm_holders, sideholder_pos), holders_side_log,
                  "PTFE_holder_side11", expHall_log, false, 0);

// Visualization attributes
holders_side_log->SetVisAttributes(gray);
holder_top_log->SetVisAttributes(gray);

// Output sample mass
const G4double PTFEholders_mass =
    12 * (holders_side_log->GetMass(false, false) / g) +
    holder_top_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Sample mass: " << PTFEholders_mass << " g" << G4endl;
G4cout << "############################" << G4endl;
