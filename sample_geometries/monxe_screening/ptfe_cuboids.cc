////////////////////////////////////////////////////////////
// To be included in the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// Shape of PTFE samples screened in the context
// of the MonXe R&D platform in Freiburg
// Sample 2019-10-10, 2020-07-07, 2020-08-24

// PTFE briks around the Ge endcap
// Five cuboids. Four 6x16x32 cm3, One 9x9x19 cm3
// Total mass: 4x6.76kg + 3.39kg = 30.42kg

// Materials

// Dimensions side briks
G4double dPTFEbrickSide_x = 60. * mm;
G4double dPTFEbrickSide_y = 160. * mm;
G4double dPTFEbrickSide_z = 320. * mm;

// Dimensions top brik
G4double dPTFEbrickTop_x = 90. * mm;
G4double dPTFEbrickTop_y = dPTFEbrickTop_x;
G4double dPTFEbrickTop_z = 190. * mm;

G4double zPosSide = zPosCuShielding + zSizeCuShielding / 2. -
                    zSizeSampleChamber + 0.5 * dPTFEbrickSide_z;
G4double zPosTop = zPosEndcap + heightEndcap / 2. + 0.5 * dPTFEbrickTop_z;

// Construction and placement
G4Box* pBox1 = new G4Box("SideBox1", 0.5 * dPTFEbrickSide_x,
                         0.5 * dPTFEbrickSide_y, 0.5 * dPTFEbrickSide_z);

G4Box* pBox2 = new G4Box("SideBox2", 0.5 * dPTFEbrickSide_y,
                         0.5 * dPTFEbrickSide_x, 0.5 * dPTFEbrickSide_z);

G4Box* pBoxTop = new G4Box("TopBox", 0.5 * dPTFEbrickTop_x,
                           0.5 * dPTFEbrickTop_y, 0.5 * dPTFEbrickTop_z);

G4LogicalVolume* pSideBrick1_log =
    new G4LogicalVolume(pBox1, Teflon, "SideBox1_log", 0, 0, 0);
G4LogicalVolume* pSideBrick2_log =
    new G4LogicalVolume(pBox2, Teflon, "SideBox2_log", 0, 0, 0);
G4LogicalVolume* pTopBrick_log =
    new G4LogicalVolume(pBoxTop, Teflon, "TopBox_log", 0, 0, 0);

new G4PVPlacement(
    0,
    G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dPTFEbrickSide_x,
                  ySizeSampleChamber / 2. - 0.5 * dPTFEbrickSide_y, zPosSide),
    pSideBrick1_log, "Teflon_LeftBrick", expHall_log, false, 0);

new G4PVPlacement(
    0,
    G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dPTFEbrickSide_x,
                  -ySizeSampleChamber / 2. + 0.5 * dPTFEbrickSide_y, zPosSide),
    pSideBrick1_log, "Teflon_RightBrick", expHall_log, false, 0);

new G4PVPlacement(
    0,
    G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dPTFEbrickSide_y,
                  ySizeSampleChamber / 2. - 0.5 * dPTFEbrickSide_x, zPosSide),
    pSideBrick2_log, "Teflon_DownBrick", expHall_log, false, 0);

new G4PVPlacement(
    0,
    G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dPTFEbrickSide_y,
                  -ySizeSampleChamber / 2. + 0.5 * dPTFEbrickSide_x, zPosSide),
    pSideBrick2_log, "Teflon_UpBrick", expHall_log, false, 0);

new G4PVPlacement(0, G4ThreeVector(0., 0., zPosTop), pTopBrick_log,
                  "Teflon_TopBrick", expHall_log, false, 0);

// Visualization attributes
pSideBrick1_log->SetVisAttributes(gray);
pSideBrick2_log->SetVisAttributes(gray);
pTopBrick_log->SetVisAttributes(gray);

// Output sample mass
G4double sidebrick_mass = pSideBrick1_log->GetMass(false, false) / g;
G4double topbrick_mass = pTopBrick_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Total PTFE mass         : " << 4 * sidebrick_mass + topbrick_mass
       << " g" << G4endl;
G4cout << "############################" << G4endl;
