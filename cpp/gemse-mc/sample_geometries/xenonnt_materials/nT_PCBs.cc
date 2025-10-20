////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// 28 PCBs in total
// Simulated as parallelepiped

// Material
G4Material *Cirlex = new G4Material("Cirlex", 1.43 * g / cm3, 4, kStateSolid);
Cirlex->AddElement(C, 22); Cirlex->AddElement(H, 10);
Cirlex->AddElement(N, 2);
Cirlex->AddElement(O, 5); 

// Dimensions of piles of 7 PCBs (GeMSE sample on 01.06.2018)
G4double pcbs_height = 286. * mm;
G4double pcbs_width = 130. * mm;
G4double pcbs_thick = 10.92 * mm;  // 7 panels together

// For the slanted 7 PCBs pannels
G4double pcbs_slanted = 2.22 * deg;
G4double pcbs_slanted_height = 281.87 * mm;
G4double pcbs_slanted_thick = 11.08 * mm;  // 7 panels together

G4Box* PCBs7_i =
    new G4Box("PCBs7_i", pcbs_width / 2., pcbs_thick / 2., pcbs_height / 2.);
G4Para* PCBs7_iii =
    new G4Para("PCBs7_iii", pcbs_slanted_thick / 2., pcbs_width / 2.,
               pcbs_slanted_height / 2., 0., -pcbs_slanted, 0.);
G4Para* PCBs7_iv =
    new G4Para("PCBs7_iv", pcbs_slanted_thick / 2., pcbs_width / 2.,
               pcbs_slanted_height / 2., 0., pcbs_slanted, 0.);

G4LogicalVolume* PCBs7_i_log =
    new G4LogicalVolume(PCBs7_i, Cirlex, "PCBs_7_one_log", 0, 0, 0);
new G4PVPlacement(0,
                  G4ThreeVector(0., pcbs_width / 2. + pcbs_thick / 2.,
                                47.4 * mm),
                  PCBs7_i_log, "PCBs7_i", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(0., -pcbs_width / 2. - pcbs_thick / 2.,
                                47.4 * mm),
                  PCBs7_i_log, "PCBs7_ii", expHall_log, false, 0);
G4LogicalVolume* PCBs7_iii_log =
    new G4LogicalVolume(PCBs7_iii, Cirlex, "PCBs7_iii_log", 0, 0, 0);
G4LogicalVolume* PCBs7_iv_log =
    new G4LogicalVolume(PCBs7_iv, Cirlex, "PCBs7_iv_log", 0, 0, 0);
new G4PVPlacement(0,
                  G4ThreeVector(outerRadiusEndcap + pcbs_thick / 2., 0.,
                                47.4 * mm),
                  PCBs7_iii_log, "PCBs7_iii", expHall_log, false, 0);
new G4PVPlacement(0,
                  G4ThreeVector(-outerRadiusEndcap - pcbs_thick / 2., 0.,
                                47.4 * mm),
                  PCBs7_iv_log, "PCBs7_iv", expHall_log, false, 0);

// Visualization attributes
PCBs7_i_log->SetVisAttributes(violet);
PCBs7_iii_log->SetVisAttributes(violet);
PCBs7_iv_log->SetVisAttributes(violet);

// Mass output
const G4double pcbs_i_mass = 2*PCBs7_i_log->GetMass(false, false)/g;
const G4double pcbs_iii_mass = 2*PCBs7_iii_log->GetMass(false, false)/g;
const G4double pcbs_mass_total = pcbs_i_mass + pcbs_iii_mass;
G4cout << "\n\n############################" << G4endl;
G4cout << "Sample mass: " << pcbs_mass_total << " g" << G4endl;
G4cout << "############################\n" << G4endl;

