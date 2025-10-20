////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// XENONnT Cu wires for field shaping rings
// Sample 2019-05-09

// PTFE spool holding + Cu wires around it
// Total mass: 14.46 kg
// Precise dimensions of the spool taken from CAD design
// Radial distance outer Cu layer - outer (top) spool surface = 25 mm

// Materials
G4Material *Cu_cylinder_mat =
    new G4Material("Cu_cylinder_mat", 7.168 * g / cm3, 2, kStateSolid);
Cu_cylinder_mat->AddMaterial(copper_mat, 0.8);
Cu_cylinder_mat->AddMaterial(air_mat, 0.2);

// Dimensions spool
G4double hSpoolOutTop = 10. * mm;
G4double hSpoolOutBot = hSpoolOutTop;
G4double hSpoolOutMid = 155. * mm;
G4double rSpoolOutTop = 110. * mm;
G4double rSpoolOutBot = rSpoolOutTop;
G4double rSpoolOutMid = 61. * mm;

G4double hSpoolInMid = 10. * mm;
G4double rSpoolInTop = 54. * mm;
G4double rSpoolInBot = rSpoolInTop;
G4double rSpoolInMid = 40. * mm;

G4double dSpoolZ0 = -0.5 * hSpoolOutMid - hSpoolOutBot;
G4double dSpoolZ1 = -0.5 * hSpoolOutMid;
G4double dSpoolZ2 = dSpoolZ1 + 0.01 * mm;
G4double dSpoolZ3 = dSpoolZ1 + hSpoolOutMid - hSpoolInMid;
G4double dSpoolZ4 = dSpoolZ3 + 0.01 * mm;
G4double dSpoolZ5 = 0.5 * hSpoolOutMid;
G4double dSpoolZ6 = dSpoolZ5 + 0.01 * mm;
G4double dSpoolZ7 = 0.5 * hSpoolOutMid + hSpoolOutTop;

G4double ZZ[] = {dSpoolZ0, dSpoolZ1, dSpoolZ2, dSpoolZ3,
                 dSpoolZ4, dSpoolZ5, dSpoolZ6, dSpoolZ7};

G4double RRout[] = {rSpoolOutBot, rSpoolOutBot, rSpoolOutMid, rSpoolOutMid,
                    rSpoolOutMid, rSpoolOutMid, rSpoolOutTop, rSpoolOutTop};

G4double RRin[] = {rSpoolInBot, rSpoolInBot, rSpoolInBot, rSpoolInBot,
                   rSpoolInMid, rSpoolInMid, rSpoolInTop, rSpoolInTop};

G4double zPosSpool = zPosCuShielding + zSizeCuShielding / 2. -
                     zSizeSampleChamber + hSpoolOutBot + 0.5 * hSpoolOutMid;

// Dimensions Cu wires cylinder
G4double hWires = hSpoolOutMid - 0.02 * mm;
G4double rWires = rSpoolOutTop - 25. * mm;

G4double zPosWires = zPosSpool;

// Construction and placement
G4Polycone *pSpool = new G4Polycone("Spool", 0, 360 * deg, 8, ZZ, RRin, RRout);
G4LogicalVolume *spool_log =
    new G4LogicalVolume(pSpool, Teflon, "spool_log", 0, 0, 0);
// new G4PVPlacement(0, G4ThreeVector(0., 0., zPosSpool),
//                  spool_log, "PTFE_spool",
//                  expHall_log, false,0);

G4Tubs *pWires = new G4Tubs("Wires", rSpoolOutMid, rWires, hWires / 2.,
                            0. * deg, 360. * deg);
G4LogicalVolume *wires_log =
    new G4LogicalVolume(pWires, Cu_cylinder_mat, "wires_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(0., 0., zPosWires), wires_log,
                  "Cu_WiresCylinder", expHall_log, false, 0);

// Visualization attributes
wires_log->SetVisAttributes(brown);
spool_log->SetVisAttributes(gray);

// Output sample mass
G4double spool_mass = spool_log->GetMass(false, false) / g;
G4double wires_mass = wires_log->GetMass(false, false) / g;
G4cout << "\n############################" << G4endl;
G4cout << "PTFE spool mass         : " << spool_mass << " g" << G4endl;
G4cout << "Cu wires (cylinder) mass: " << wires_mass << " g" << G4endl;
G4cout << "############################" << G4endl;
