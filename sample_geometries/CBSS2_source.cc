////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// CBSS2 calibration source used for the first GeMSE instrument paper (2016)
// Extracted (untouched) from the main construction class in 2021

// Dimensions
G4double outerRadiusPS = 3.83*cm;
G4double innerRadiusPS = 3.68*cm;
G4double heightPS = 3.9*cm;
G4double heightPS_top = 0.12*cm;
G4double heightPS_bottom = 0.15*cm;
G4double dPS_bottom = 0.1*cm;
G4double zPosPS = zPosEndcap+heightEndcap/2.+heightPS/2.+overlap;

G4double heightCBSS2 = 2.82*cm;
G4double zPosCBSS2 = zPosEndcap+heightEndcap/2. + heightCBSS2/2.
                     + dPS_bottom+heightPS_bottom + 2.*overlap;
G4cout << "z-position of CBBS source: " << zPosCBSS2/cm << " cm" << G4endl;

// Materials
G4Material* ps_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

// Construction and placement

// PS container (Semadeni)
G4Tubs* PSwall_tube = new G4Tubs ("PSwall_tube", innerRadiusPS, outerRadiusPS,
                                  heightPS/2., startAngle, spanningAngle);
G4Tubs* PSbottom_tube = new G4Tubs ("PSbottom_tube", 0.*cm, innerRadiusPS+0.001*cm,
                                    heightPS_bottom/2., startAngle, spanningAngle);
G4Tubs* PStop_tube = new G4Tubs	("PStop_tube", 0.*cm, innerRadiusPS+0.001*cm,
                                 heightPS_top/2., startAngle, spanningAngle);
G4UnionSolid* PS_uni1 = new G4UnionSolid("PS_uni1", PSwall_tube, PStop_tube, 0,
                                         G4ThreeVector(0.,0.,heightPS/2.-heightPS_top/2.-0.001*cm));
G4UnionSolid* PS_uni2 = new G4UnionSolid("PS_uni2", PS_uni1,PSbottom_tube, 0,
                                         G4ThreeVector(0., 0., -heightPS/2.+heightPS_bottom/2.+dPS_bottom));

G4LogicalVolume* PS_log = new G4LogicalVolume(PS_uni2, ps_mat, "PS_log", 0, 0, 0);

new G4PVPlacement(0, G4ThreeVector(0., 0., zPosPS),
                  PS_log, "PS", expHall_log, false, 0);

// Source
G4Tubs*	CBSS2_tube = new G4Tubs ("CBSS2_tube", 0.*cm, innerRadiusPS-overlap,
                                 heightCBSS2/2., startAngle, spanningAngle);

G4LogicalVolume* CBSS2_log = new G4LogicalVolume(CBSS2_tube, matrix_mat, "CBSS2_log", 0, 0, 0);

new G4PVPlacement(0, G4ThreeVector(0., 0., zPosCBSS2),
                  CBSS2_log, "CBSS2", expHall_log, false, 0);

// Visualization attributes
G4VisAttributes* violet = new G4VisAttributes(G4Colour(0.5,0.0,1.0));
G4VisAttributes* lightblue = new G4VisAttributes(G4Colour(0.0,0.5,1.0));
PS_log->SetVisAttributes(lightblue);
CBSS2_log->SetVisAttributes(violet);

// Output sample mass
G4double dContainer_mass = PS_log->GetMass(false, false) / g;
G4double dSource_mass = CBSS2_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Calibration source mass         : " << dSource_mass << " g" << G4endl;
G4cout << "Calibration container mass         : " << dContainer_mass << " g" << G4endl;
G4cout << "############################" << G4endl;

// Untracked calibration source from the ancient times (maybe the lab WT-20 source, or the Ba-133 one)
/*
G4Material* pmma_mat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");

G4Box* source_box = new G4Box("source_box", 1.675*cm, 0.55*cm, 0.1*cm);
G4Sphere* hole_source = new G4Sphere("hole_source", 0, 0.05*cm,
                                     0, 360.*deg, 0., 180.*deg);
G4SubtractionSolid* source_sub =
    new G4SubtractionSolid("source_sub", source_box, hole_source, 0, G4ThreeVector(0,0,0));

G4LogicalVolume* source_log =
    new G4LogicalVolume(source_sub,pmma_mat,"source_log",0,0,0); new
G4PVPlacement(0,G4ThreeVector(0,0,4.75*cm), source_log, "source", expHall_log, false, 0);
*/
