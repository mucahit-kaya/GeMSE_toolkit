////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// XENONnT high voltage connectors
// Sample 2019-02-11

// Per connector pair (1 male and 1 female):
// - 28.5 g PTFE
// - 11.9 g Cu
// - 1.7 g SS
// Total screened mass: 23*(28.5 + 11.9 + 1.7) = 968.3 g

// Materials
G4Material* HVconnectorsCompact_mat =
    new G4Material("HVconnectorsCompact_mat", 4.32 * g / cm3, 3, kStateSolid);
HVconnectorsCompact_mat->AddMaterial(SS304LSteel, 0.04);
HVconnectorsCompact_mat->AddMaterial(copper_mat, 0.28);
HVconnectorsCompact_mat->AddMaterial(Teflon, 0.68);

G4Material* HVconnectors_mat =
    new G4Material("HVconnectors_mat", 1.88 * g / cm3, 2, kStateSolid);
HVconnectors_mat->AddMaterial(HVconnectorsCompact_mat, 0.44);
HVconnectors_mat->AddMaterial(air_mat, 0.56);

// Dimensions
G4double hvcon_height = 25. * mm;
G4double hvcon_thick = 204. * mm;
G4double hvcon_width = 102. * mm;
G4double zPosHVcon = zPosEndcap + heightEndcap / 2. + hvcon_height / 2.;
// G4cout << "zPosHVcon = " << zPosHVcon/mm << " mm" << G4endl;

G4Box* hvConnectorsBrick = new G4Box("hvConnectorsBrick", hvcon_width / 2.,
                                     hvcon_thick / 2., hvcon_height / 2.);
G4LogicalVolume* hvConnectorsBrick_log = new G4LogicalVolume(
    hvConnectorsBrick, HVconnectors_mat, "hvConnectorsBrick_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., zPosHVcon), hvConnectorsBrick_log,
                  "hvConnectorsBrick", expHall_log, false, 0);

// Visualization attributes
G4VisAttributes* violet = new G4VisAttributes(G4Colour(0.5, 0.0, 1.0));
hvConnectorsBrick_log->SetVisAttributes(violet);

// Output sample mass
const G4double HVconnectors_mass =
    hvConnectorsBrick_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "Sample mass: " << HVconnectors_mass << " g" << G4endl;
G4cout << "############################" << G4endl;
