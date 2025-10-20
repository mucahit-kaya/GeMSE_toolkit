////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// XENONnT Cu bricks for the XENONnT top and bottom PMT plates
// Sample 2020-02-18

// 40 briks;
// approx: 150-155 mm high, 74-79 mm long, 20-24 mm wide

// Dimensions
G4double dCu_height_l = 156. * mm;
G4double dCu_height_s = 151. * mm;

G4double dCu_width_l = 24. * mm;
G4double dCu_width_s = 20. * mm;

G4double dCu_length_l = 79. * mm;
G4double dCu_length_s = 74. * mm;

G4double zPosBotLayer_s = zPosCuShielding + zSizeCuShielding / 2. -
                          zSizeSampleChamber + 0.5 * dCu_height_s;
G4double zPosBotLayer_l = zPosCuShielding + zSizeCuShielding / 2. -
                          zSizeSampleChamber + 0.5 * dCu_height_l;

G4double dBrickSeparation = 0.5 * mm;

G4RotationMatrix rm_bricks_Z;
rm_bricks_Z.rotateZ(90. * deg);

// Bricks construction

G4Box* pBrick_a =
    new G4Box("Brick_a",  // SLS
              0.5 * dCu_width_s, 0.5 * dCu_length_l, 0.5 * dCu_height_s);
G4Box* pBrick_b =
    new G4Box("Brick_b",  // LLS
              0.5 * dCu_width_l, 0.5 * dCu_length_l, 0.5 * dCu_height_s);
G4Box* pBrick_c =
    new G4Box("Brick_c",  // LSS
              0.5 * dCu_width_l, 0.5 * dCu_length_s, 0.5 * dCu_height_s);
G4Box* pBrick_d =
    new G4Box("Brick_d",  // SSS
              0.5 * dCu_width_s, 0.5 * dCu_length_s, 0.5 * dCu_height_s);
G4Box* pBrick_e =
    new G4Box("Brick_e",  // LLL
              0.5 * dCu_width_l, 0.5 * dCu_length_l, 0.5 * dCu_height_l);
// G4Box* pBrick_f = new G4Box("Brick_f", //LSL
//                            0.5*dCu_width_l, 0.5*dCu_length_s,
//                            0.5*dCu_height_l);
G4Box* pBrick_g =
    new G4Box("Brick_g",  // SLL
              0.5 * dCu_width_s, 0.5 * dCu_length_l, 0.5 * dCu_height_l);

G4LogicalVolume* CuBrick_a =
    new G4LogicalVolume(pBrick_a, copper_mat, "CuBrick_a_log", 0, 0, 0);
G4LogicalVolume* CuBrick_b =
    new G4LogicalVolume(pBrick_b, copper_mat, "CuBrick_b_log", 0, 0, 0);
G4LogicalVolume* CuBrick_c =
    new G4LogicalVolume(pBrick_c, copper_mat, "CuBrick_c_log", 0, 0, 0);
G4LogicalVolume* CuBrick_d =
    new G4LogicalVolume(pBrick_d, copper_mat, "CuBrick_d_log", 0, 0, 0);
G4LogicalVolume* CuBrick_e =
    new G4LogicalVolume(pBrick_e, copper_mat, "CuBrick_d_log", 0, 0, 0);
// G4LogicalVolume* CuBrick_f =
//    new G4LogicalVolume(pBrick_f, copper_mat, "CuBrick_d_log",0,0,0);
G4LogicalVolume* CuBrick_g =
    new G4LogicalVolume(pBrick_g, copper_mat, "CuBrick_d_log", 0, 0, 0);

// Bricks placement
// See pictures displayed in http://login.physik.uni-freiburg.de:8284/GeMSE/229
// Brick_101 is top left brick, Brick_201 top center brik, etc.
// Numbering from top to bottom and left to right

//////////////////
// Bottom layer //
//////////////////

new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dCu_width_s,
                                -ySizeSampleChamber / 2. + 0.5 * dCu_length_l,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_101", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. + 1.5 * dCu_width_s +
                                    dBrickSeparation,
                                -ySizeSampleChamber / 2. + 0.5 * dCu_length_l,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_102", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. + 2.5 * dCu_width_s +
                                    2 * dBrickSeparation,
                                -ySizeSampleChamber / 2. + 0.5 * dCu_length_l,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_103", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. +
                                    3 * (dCu_width_s + dBrickSeparation) +
                                    0.5 * dCu_width_l,
                                -ySizeSampleChamber / 2. + 0.5 * dCu_length_l,
                                zPosBotLayer_l),
                  CuBrick_e, "CuBrick_Bot_104", expHall_log, false, 0);

G4ThreeVector sample_pos = G4ThreeVector(
    xSizeSampleChamber / 2. - 1.5 * dCu_length_s - dBrickSeparation,
    -ySizeSampleChamber / 2. + 0.5 * dCu_width_s, zPosBotLayer_s);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_105", expHall_log, false, 0);
sample_pos =
    sample_pos + G4ThreeVector(dCu_length_s - dCu_length_l - dBrickSeparation,
                               dCu_width_s + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_106", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0, dCu_width_s + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_107", expHall_log, false, 0);

sample_pos =
    G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dCu_length_s,
                  -ySizeSampleChamber / 2. + 0.5 * dCu_width_s, zPosBotLayer_s);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_108", expHall_log, false, 0);
sample_pos =
    sample_pos +
    G4ThreeVector(0.5 * (dCu_length_s - dCu_length_l),
                  0.5 * (dCu_width_s + dCu_width_l) + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_b,
                  "CuBrick_Bot_109", expHall_log, false, 0);
sample_pos =
    sample_pos +
    G4ThreeVector(0.5 * (dCu_length_l - dCu_length_s),
                  0.5 * (dCu_width_s + dCu_width_l) + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_110", expHall_log, false, 0);

new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dCu_width_s,
                                -ySizeSampleChamber / 2. + 1.5 * dCu_length_l +
                                    dBrickSeparation,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_201", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-xSizeSampleChamber / 2. + 1.5 * dCu_width_s +
                                    dBrickSeparation,
                                -ySizeSampleChamber / 2. + 1.5 * dCu_length_l +
                                    dBrickSeparation,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_202", expHall_log, false, 0);
new G4PVPlacement(
    0,
    G4ThreeVector(-xSizeSampleChamber / 2. +
                      2 * (dCu_width_s + dBrickSeparation) + 0.5 * dCu_width_l,
                  -ySizeSampleChamber / 2. + 1.5 * dCu_length_l + 5. * mm,
                  zPosBotLayer_l),
    CuBrick_e, "CuBrick_Bot_203", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 2.5 * dCu_width_s -
                                    2 * dBrickSeparation,
                                ySizeSampleChamber / 2. - 1.5 * dCu_length_l -
                                    dBrickSeparation,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_204", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 1.5 * dCu_width_s -
                                    dBrickSeparation,
                                ySizeSampleChamber / 2. - 1.5 * dCu_length_l -
                                    dBrickSeparation,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_205", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dCu_width_s,
                                ySizeSampleChamber / 2. - dCu_length_s -
                                    0.5 * dCu_length_l - dBrickSeparation,
                                zPosBotLayer_l),
                  CuBrick_g, "CuBrick_Bot_206", expHall_log, false, 0);

sample_pos = G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dCu_length_l,
                           ySizeSampleChamber / 2. - 1.5 * dCu_width_s -
                               dCu_width_l - 2 * dBrickSeparation,
                           zPosBotLayer_s);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_a,
                  "CuBrick_Bot_301", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0, dCu_width_s + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_a,
                  "CuBrick_Bot_302", expHall_log, false, 0);
sample_pos =
    sample_pos +
    G4ThreeVector(0.5 * (dCu_length_s - dCu_length_l),
                  0.5 * (dCu_width_s + dCu_width_l) + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_c,
                  "CuBrick_Bot_303", expHall_log, false, 0);
sample_pos = G4ThreeVector(
    -xSizeSampleChamber / 2. + 1.5 * dCu_length_l + dBrickSeparation,
    ySizeSampleChamber / 2. - 2.5 * dCu_width_s - 2 * dBrickSeparation,
    zPosBotLayer_s);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_a,
                  "CuBrick_Bot_304", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0.5 * (dCu_length_s - dCu_length_l),
                                        dCu_width_s + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_d,
                  "CuBrick_Bot_305", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0.5 * (dCu_length_s - dCu_length_l),
                                        dCu_width_s + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_Z, sample_pos), CuBrick_a,
                  "CuBrick_Bot_306", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 3.5 * dCu_width_s -
                                    3 * dBrickSeparation,
                                ySizeSampleChamber / 2. - 0.5 * dCu_length_s,
                                zPosBotLayer_s),
                  CuBrick_d, "CuBrick_Bot_307", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 2.5 * dCu_width_s -
                                    2 * dBrickSeparation,
                                ySizeSampleChamber / 2. - 0.5 * dCu_length_l,
                                zPosBotLayer_s),
                  CuBrick_a, "CuBrick_Bot_308", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 1.5 * dCu_width_s -
                                    dBrickSeparation,
                                ySizeSampleChamber / 2. - 0.5 * dCu_length_l,
                                zPosBotLayer_s),
                  CuBrick_a, "CuBrick_Bot_309", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dCu_width_s,
                                ySizeSampleChamber / 2. - 0.5 * dCu_length_s,
                                zPosBotLayer_s),
                  CuBrick_d, "CuBrick_Bot_310", expHall_log, false, 0);

//////////////////
// Middle layer //
//////////////////

G4RotationMatrix rm_bricks_mid;
rm_bricks_mid.rotateZ(90. * deg);
rm_bricks_mid.rotateY(90. * deg);

sample_pos =
    G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dCu_height_s + 8. * mm,
                  -ySizeSampleChamber / 2. + 0.5 * dCu_width_l + 3. * mm,
                  zPosBotLayer_l + 0.5 * (dCu_length_s + dCu_height_l));
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_c,
                  "CuBrick_Mid_101", expHall_log, false, 0);
sample_pos =
    sample_pos + G4ThreeVector(-3. * mm + 0.5 * (dCu_height_l - dCu_height_s),
                               dCu_width_l + dBrickSeparation,
                               0.5 * (dCu_length_l - dCu_length_s));
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_102", expHall_log, false, 0);
sample_pos =
    sample_pos + G4ThreeVector(+3. * mm, dCu_width_l + 4 * dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_103", expHall_log, false, 0);

rm_bricks_mid.rotateZ(90. * deg);
sample_pos =
    G4ThreeVector(xSizeSampleChamber / 2. - 0.5 * dCu_width_l,
                  -ySizeSampleChamber / 2. + 0.5 * dCu_height_l + 3. * mm,
                  zPosBotLayer_l + 0.5 * (dCu_length_l + dCu_height_l));
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_104", expHall_log, false, 0);
sample_pos =
    sample_pos + G4ThreeVector(-dCu_width_l - dBrickSeparation, -3. * mm, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_105", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(-dCu_width_l - 3. * mm, +1. * mm, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_106", expHall_log, false, 0);

sample_pos =
    G4ThreeVector(-xSizeSampleChamber / 2. + 0.5 * dCu_width_l + 1. * mm,
                  ySizeSampleChamber / 2. - 0.5 * dCu_height_s,
                  zPosBotLayer_l + 0.5 * (dCu_length_l + dCu_height_l));
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_b,
                  "CuBrick_Mid_201", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(dCu_width_l + dBrickSeparation, 0, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_b,
                  "CuBrick_Mid_202", expHall_log, false, 0);
sample_pos = sample_pos +
             G4ThreeVector(dCu_width_l + dBrickSeparation + 3. * mm,
                           0.5 * (dCu_height_s - dCu_height_l) - 2. * mm, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_203", expHall_log, false, 0);

rm_bricks_mid.rotateZ(-90. * deg);
sample_pos = G4ThreeVector(
    xSizeSampleChamber / 2. - 0.5 * dCu_height_s - 3. * mm,
    ySizeSampleChamber / 2. - 2.5 * dCu_width_l - 2 * dBrickSeparation,
    zPosBotLayer_l + 0.5 * (dCu_length_l + dCu_height_l));
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_b,
                  "CuBrick_Mid_204", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0, dCu_width_l + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_b,
                  "CuBrick_Mid_205", expHall_log, false, 0);
sample_pos =
    sample_pos + G4ThreeVector(0.5 * (dCu_height_s - dCu_height_l) + 2 * mm,
                               dCu_width_l + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_mid, sample_pos), CuBrick_e,
                  "CuBrick_Mid_206", expHall_log, false, 0);

///////////////
// Top layer //
///////////////

G4RotationMatrix rm_bricks_top;
rm_bricks_top.rotateY(90. * deg);

sample_pos = G4ThreeVector(
    0, -0.5 * (dCu_length_l + dBrickSeparation),
    zPosBotLayer_l + dCu_length_l + 0.5 * (dCu_height_l + dCu_width_l));
new G4PVPlacement(G4Transform3D(rm_bricks_top, sample_pos), CuBrick_e,
                  "CuBrick_Top_1", expHall_log, false, 0);
sample_pos = sample_pos + G4ThreeVector(0, dCu_length_l + dBrickSeparation, 0);
new G4PVPlacement(G4Transform3D(rm_bricks_top, sample_pos), CuBrick_e,
                  "CuBrick_Top_2", expHall_log, false, 0);

// Visualization attributes
CuBrick_a->SetVisAttributes(gray);
CuBrick_b->SetVisAttributes(gray);
CuBrick_c->SetVisAttributes(gray);
CuBrick_d->SetVisAttributes(gray);
CuBrick_e->SetVisAttributes(gray);
// CuBrick_f->SetVisAttributes(gray);
CuBrick_g->SetVisAttributes(gray);

// Output sample mass
const G4double dCu_ScreenedMass = 6 * CuBrick_a->GetMass(false, false) / g +
                                  5 * CuBrick_b->GetMass(false, false) / g +
                                  2 * CuBrick_c->GetMass(false, false) / g +
                                  8 * CuBrick_d->GetMass(false, false) / g +
                                  11 * CuBrick_e->GetMass(false, false) / g +
                                  8 * CuBrick_g->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Cu screened mass: " << dCu_ScreenedMass << " g" << G4endl;
G4cout << "############################" << G4endl;
