////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// Vue des Alpes cavern shape from the initial (2015) GeMSE muon background simulations
// Extracted from the source code linked under
// https://wiki.uni-freiburg.de/app/doku.php?id=start:gemse:analysis:initial_bkg_fit
// and slightly corrected to meet the current variable naming

// Named '*deprecated' since no extensive validation was made before upload. It is no
// longer needed for muon simulations, but the does match very well the floor/detector position, etc.

// Materials
G4Material* standardrock_mat = new G4Material("Standard_Rock", z=11.,
                                                a=22.*g/mole, density=2.65*g/cm3);    
// Dimensions
G4double widthCavern = 7.*m;
G4double lengthCavern = 7.60*m;
G4double radiusCavern = 3.50*m;
G4double offsetRadius = 2.55*m;
G4double thicknessRock = 2.*m;
G4double thicknessWall = 20.*cm;
G4double widthRoom = 3.95*m;

G4double zPosFloor =
   zPosCuShielding-(zSizeSampleChamber/2.+d_CuShielding_sides
                    +d_innerPbShielding+d_outerPbShielding);
G4double xSizeShielding =
   xSizeSampleChamber+2.*d_CuShielding_sides+2.*d_innerPbShielding+2.*d_outerPbShielding;
G4double ySizeShielding =
   ySizeSampleChamber+2.*d_CuShielding_sides+2.*d_innerPbShielding+2.*d_outerPbShielding;
G4double zSizeShielding =
   zSizeSampleChamber+2.*d_CuShielding_sides+2.*d_innerPbShielding+2.*d_outerPbShielding;
G4double xPosCavern = -xSizeShielding/2.+widthCavern/2.-20*cm;
G4double zPosCavern = zPosFloor+(offsetRadius/2.-thicknessRock/2.);

// Build
G4Tubs*	Cavern_tube = new G4Tubs("Cavern_tube",
                                 0.*m, radiusCavern, lengthCavern/2., 0.*deg, 180.*deg);
G4Box* Cavern_box = new G4Box("Cavern_box",
                              widthCavern/2., lengthCavern/2., offsetRadius/2.+overlap);
G4Tubs*	CavernOut_tube =
   new G4Tubs("CavernOut_tube", 0.*m, radiusCavern+thicknessRock, lengthCavern/2.+thicknessRock,
              0.*deg, 180.*deg);
G4Box* CavernOut_box =
   new G4Box("CavernOut_box", widthCavern/2.+thicknessRock, lengthCavern/2.+thicknessRock,
             (offsetRadius+thicknessRock)/2.+overlap);
G4Box* Wall_box =
   new G4Box("Wall_box", thicknessWall/2., lengthCavern/2.+overlap,(offsetRadius+radiusCavern)/2.+overlap);
G4UnionSolid* Cavern_in =
   new G4UnionSolid("Cavern_in", Cavern_box,Cavern_tube,
                    G4Transform3D(rm2,G4ThreeVector(0.,0.,offsetRadius/2.)));
G4UnionSolid* Cavern_out =
   new G4UnionSolid("Cavern_out", CavernOut_box,CavernOut_tube,
                    G4Transform3D(rm2,G4ThreeVector(0.,0.,(offsetRadius+thicknessRock)/2.)));
G4SubtractionSolid* Cavern_sub =
   new G4SubtractionSolid("Cavern_sub", Cavern_out,Cavern_in,0,
                          G4ThreeVector(0.,0.,thicknessRock/2.));
G4UnionSolid* Cavern_uni =
   new G4UnionSolid("Cavern_uni", Cavern_sub,Wall_box,0,
                    G4ThreeVector(-widthCavern/2.+widthRoom,0.,(radiusCavern+thicknessRock)/2.));

G4LogicalVolume* Cavern_log = new G4LogicalVolume(Cavern_uni, standardrock_mat, "Cavern_log", 0, 0, 0);
new G4PVPlacement(0, G4ThreeVector(xPosCavern,0.,zPosCavern), Cavern_log, "Cavern", expHall_log, false, 0);
