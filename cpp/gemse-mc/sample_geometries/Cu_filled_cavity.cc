////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// Copper filled cavity for sensitivity studies (2018)

G4double heightCuHsg_tube_filled = zSizeSampleChamber-zPosCuShielding-zSizeCuShielding/2.+zPosEndcap+heightEndcap/2.-0.001*cm;

G4Box* SampleCavity_box = new G4Box("SampleCavity_box", xSizeSampleChamber/2., ySizeSampleChamber/2.,
                                    zSizeSampleChamber/2.+0.001*cm);
G4Tubs* CuHsg_tube_filled = new G4Tubs ("CuHsg_tube_filled", 0.*cm, outerRadiusEndcap,
                                        heightCuHsg_tube_filled, startAngle, spanningAngle);
G4SubtractionSolid* CuFilling = new G4SubtractionSolid("CuFilling", SampleCavity_box, CuHsg_tube_filled, 0,
                                                       G4ThreeVector(0.,0.,-zSizeSampleChamber/2.));

G4LogicalVolume* CuFilling_log = new G4LogicalVolume(CuFilling, copper_mat, "CuFilling_log", 0, 0, 0);

new G4PVPlacement(0, G4ThreeVector(0., 0., zPosCuShielding+zSizeCuShielding/2.-zSizeSampleChamber/2.+0.001*cm),
                  CuFilling_log, "CuFilling", expHall_log, false, 0);

G4cout << "Height of the copper tower: " << heightCuHsg_tube_filled/2./cm << " cm" << G4endl;

// Visualization attributes
CuFilling_log->SetVisAttributes(green);

// Output sample mass
G4double dCu_mass = CuFilling_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Cu mass : " << dCu_mass << " g" << G4endl;
G4cout << "############################" << G4endl;

