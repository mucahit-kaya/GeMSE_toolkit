////////////////////////////////////////////////////////////
// To be called from the GeMSE_DetectorConstruction class //
////////////////////////////////////////////////////////////

// - If the holder is not contructed, the PMTs designated to that holder will
//   not be constructed, regardless of the number of PMTs specified
// - A single PMT on the endcap at the last line
// - For just one PMT on the endcap, for example, set all holders to false and
//   uncomment the last line.

G4double pi_g = 3.141592653589793;

// IMPORTANT: Center of the cavity is at the z coordinate 7.94 cm (check MC
// output from GeMSE_DetectorConstruction.cc)
G4double zCavityCenter = 7.94 * cm;
// ... and position of the endcap
G4double zEndcap = 3.95 * cm;

G4double PMTsZoffset = 43 * mm;   // Vertical Offset of the lowest PMT
G4double PMTsSpacing = 80. * mm;  // Distance between the PMTs central axis
G4double PMTlenght = 114. * mm;

G4double HolderWidth = 100. * mm;
// G4double HolderLenght         = 101.*mm;
G4double HolderLenght = 97. * mm;
// G4double HolderHeight_short   = 246*mm;
G4double HolderHeight_long = 326 * mm;

G4LogicalVolume* HolderLong_log = ConstructPMTholder_long();
G4LogicalVolume* PMTR11410_log = ConstructPmtR11410();

std::vector<G4VPhysicalVolume*>* PMTs_vec =
    new std::vector<G4VPhysicalVolume*>();

// GATOR
// G4double PMT1stColX	= 114.5*mm;
// G4double PMT1stColY	= 67.5*mm;
// G4double PMT1stColZ	= PMTsZoffset-zSizeSampleChamber/2.;

G4double PMT1stColX = 100. * mm;
G4double PMT1stColY = 64. * mm;
G4double PMT1stColZ =
    PMTsZoffset - (zSizeSampleChamber - HolderHeight_long) / 2.;

// Distance between the PMTs central axis
G4ThreeVector PMT_VertStep(0. * mm, 0. * mm, PMTsSpacing);
G4double HolderHrzOffset = HolderLenght - PMTlenght;
// G4double cos15 = cos(15*pi_g/180);
// G4double sin15 = sin(15*pi_g/180);
G4double cos14 = cos(14 * pi_g / 180);
G4double sin14 = sin(14 * pi_g / 180);

// Added "zCavityCenter" to all the previously (Gator) defined z coordinates for
// the PMT column offset
G4ThreeVector PMT1stCol_offset(PMT1stColY, -PMT1stColX,
                               zCavityCenter + PMTsZoffset -
                                   zSizeSampleChamber / 2.);
G4ThreeVector PMT2ndCol_offset(-PMT1stColY, -PMT1stColX,
                               zCavityCenter + PMTsZoffset -
                                   zSizeSampleChamber / 2.);
G4ThreeVector PMT3rdCol_offset(71. * mm - HolderHrzOffset * cos14,
                               68. * mm + HolderHrzOffset * sin14,
                               zCavityCenter + PMTsZoffset -
                                   zSizeSampleChamber / 2.);
// G4ThreeVector
// PMT1stCol_offset(71.*mm-HolderHrzOffset*cos14, 68.*mm+HolderHrzOffset*sin14,zCavityCenter+PMTsZoffset-zSizeSampleChamber/2.);
// G4ThreeVector
// PMT2ndCol_offset(-PMT1stColY,-PMT1stColX,zCavityCenter+PMTsZoffset-zSizeSampleChamber/2.);
// G4ThreeVector
// PMT3rdCol_offset(-PMT1stColX,-PMT1stColY,zCavityCenter+PMTsZoffset-zSizeSampleChamber/2.);
// G4ThreeVector
// PMT4thCol_offset(-PMT1stColY,PMT1stColX,PMTsZoffset-(zSizeSampleChamber/2.)+80*mm);
// //The short column (80mm = teflon table height)

G4RotationMatrix PMT1stCol_rot, PMT2ndCol_rot, PMT3rdCol_rot, PMT4thCol_rot;
PMT1stCol_rot.rotateY(-90. * deg);
PMT1stCol_rot.rotateZ(-104. * deg);
PMT2ndCol_rot.rotateX(-90. * deg);
PMT2ndCol_rot.rotateZ(14. * deg);
PMT3rdCol_rot.rotateY(90. * deg);
PMT3rdCol_rot.rotateZ(166. * deg);
// PMT4thCol_rot.rotateX(90.*deg);
// PMT4thCol_rot.rotateZ(-15.*deg);

G4ThreeVector PMTpos;
std::stringstream PMTVolName;

//'i' range => Number of PMTs + 1
for (G4int i = 1; i < 10; i++) {
  // char index[100]="";
  PMTVolName.str("");
  // sprintf(index,"%d",i);
  PMTVolName << "PMT" << i << "_phys";
  // G4cout << PMTVolName.str() << G4endl;

  // Below written for 10 PMTs (3,3,3,0), i.e., fourth holder commented out
  if (i <= 3) {
    PMTpos = PMT1stCol_offset + ((i - 1) % 3) * PMT_VertStep;
    if (true)
      PMTs_vec->push_back(
          new G4PVPlacement(G4Transform3D(PMT1stCol_rot, PMTpos), PMTR11410_log,
                            PMTVolName.str(), expHall_log, false, 0));
  }

  else if (3 < i && i <= 6) {
    PMTpos = PMT2ndCol_offset + ((i - 1) % 3) * PMT_VertStep;
    if (true)
      PMTs_vec->push_back(
          new G4PVPlacement(G4Transform3D(PMT2ndCol_rot, PMTpos), PMTR11410_log,
                            PMTVolName.str(), expHall_log, false, 0));
  }

  else if (6 < i && i < 10) {
    PMTpos = PMT3rdCol_offset + ((i - 1) % 3) * PMT_VertStep;
    if (true)
      PMTs_vec->push_back(
          new G4PVPlacement(G4Transform3D(PMT3rdCol_rot, PMTpos), PMTR11410_log,
                            PMTVolName.str(), expHall_log, false, 0));
  }

  //   else if(<12 && i<=16){
  //     PMTpos = PMT4thCol_offset + ((i-1)%4)*PMT_VertStep;
  //     if(true) PMTs_vec -> push_back(new
  //     G4PVPlacement(G4Transform3D(PMT4thCol_rot,PMTpos),PMTR11410_log,PMTVolName.str(),expHall_log,false,0));
  //   }
}

G4double baseHeight1 = 7.0 * cm;
G4double endcapHeight3 = 0.635 * cm;
G4double endcapHeight1 = 12.905 * cm;

G4double endcapPos_x =
    0.0 * cm;  // base is 1.0cm from wall, decrease x to decrease separation
G4double endcapPos_y = 0.0 * cm;
G4double endcapPos_z =
    -(2. * cm + 0.5 * zSizeSampleChamber) + endcapHeight3 + baseHeight1 +
    0.5 * endcapHeight1 +
    (0.001 * mm);  // Added a little shift to avoid surfaces ovelapping
// G4double endcapPos_z = -1.4325*cm; //base is 1.0cm from bottom, decrease z to
// lower base G4ThreeVector endcap_Shift(endcapPos_x,endcapPos_y,endcapPos_z); //
// <-- From Gator
G4ThreeVector endcap_Shift(endcapPos_x, endcapPos_y, zEndcap);

G4RotationMatrix Holder1_rot;
Holder1_rot.rotateZ(-14. * deg);
G4ThreeVector Holder1pos(PMT1stColY - HolderHrzOffset * sin14,
                         -PMT1stColX - HolderHrzOffset * cos14,
                         zCavityCenter -
                             (zSizeSampleChamber - HolderHeight_long) / 2.);
// G4ThreeVector Holder1pos(PMT1stColY, -PMT1stColX,
// zCavityCenter-(zSizeSampleChamber-HolderHeight_long)/2.);
G4VPhysicalVolume* Holder1_phys =
    new G4PVPlacement(G4Transform3D(Holder1_rot, Holder1pos), HolderLong_log,
                      "Holder1_phys", expHall_log, false, 0);

G4RotationMatrix Holder2_rot;
Holder2_rot.rotateZ(14. * deg);
G4ThreeVector Holder2pos(-(PMT1stColY - HolderHrzOffset * sin14),
                         -PMT1stColX - HolderHrzOffset * cos14,
                         zCavityCenter -
                             (zSizeSampleChamber - HolderHeight_long) / 2.);
G4VPhysicalVolume* Holder2_phys =
    new G4PVPlacement(G4Transform3D(Holder2_rot, Holder2pos), HolderLong_log,
                      "Holder2_phys", expHall_log, false, 0);

G4RotationMatrix Holder3_rot;
Holder3_rot.rotateZ(76. * deg);
G4ThreeVector Holder3pos(71. * mm, 68. * mm,
                         zCavityCenter -
                             (zSizeSampleChamber - HolderHeight_long) / 2.);
G4VPhysicalVolume* Holder3_phys =
    new G4PVPlacement(G4Transform3D(Holder3_rot, Holder3pos), HolderLong_log,
                      "Holder3_phys", expHall_log, false, 0);

// G4RotationMatrix Holder1_rot;
// Holder1_rot.rotateZ(75.*deg);
// //G4ThreeVector Holder1pos(PMT1stColX+HolderHrzOffset*cos15,
// PMT1stColY-HolderHrzOffset*sin15, (HolderHeight_long-zSizeSampleChamber)/2.);
// // <-- From Gator G4ThreeVector Holder1pos(PMT1stColX+HolderHrzOffset*cos15,
// PMT1stColY-HolderHrzOffset*sin15,
// zCavityCenter-(zSizeSampleChamber-HolderHeight_long)/2.); G4VPhysicalVolume*
// Holder1_phys = new G4PVPlacement(G4Transform3D(Holder1_rot,Holder1pos),
// HolderLong_log, "Holder1_phys", expHall_log, false, 0);

// G4RotationMatrix Holder2_rot;
// Holder2_rot.rotateZ(-15.*deg);
// G4ThreeVector Holder2pos(PMT1stColY-HolderHrzOffset*sin15,
// -PMT1stColX-HolderHrzOffset*cos15,
// zCavityCenter-(zSizeSampleChamber-HolderHeight_long)/2.); G4VPhysicalVolume*
// Holder2_phys = new G4PVPlacement(G4Transform3D(Holder2_rot,Holder2pos),
// HolderLong_log, "Holder2_phys", expHall_log, false, 0);

// G4RotationMatrix Holder3_rot;
// Holder3_rot.rotateZ(-105.*deg);
// G4ThreeVector Holder3pos(-PMT1stColX-HolderHrzOffset*cos15,
// -PMT1stColY+HolderHrzOffset*sin15,
// zCavityCenter-(zSizeSampleChamber-HolderHeight_long)/2.); G4VPhysicalVolume*
// Holder3_phys = new G4PVPlacement(G4Transform3D(Holder3_rot,Holder3pos),
// HolderLong_log, "Holder3_phys", expHall_log, false, 0);

// G4RotationMatrix Holder4_rot;
// Holder4_rot.rotateZ(-195.*deg);
// G4ThreeVector
// Holder4pos(-PMT1stColY+HolderHrzOffset*sin15,PMT1stColX+HolderHrzOffset*cos15,(HolderHeight_short-zSizeSampleChamber)/2.+80*mm);
// //The short column (80mm = teflon table height)
// G4VPhysicalVolume* Holder4_phys = new
// G4PVPlacement(G4Transform3D(Holder4_rot,Holder4pos),HolderShort_log,"Holder4_phys",expHall_log,false,0);

// A PMT on top of the end-cap
// G4VPhysicalVolume* PMT_envel_phys13 = new G4PVPlacement(0,endcap_Shift +
// G4ThreeVector(0., 0., 0.0001*mm), PMTR11410_log, "PMTonTop", expHall_log,
// false, 0);
