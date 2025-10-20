=======
History
=======

2.0.0 (2021-05-31)
------------------
* Miscellaneous changes before next release (#14)
* Muon generator in ParticleSource (#12)
* Muon veto panels and sensitive detector (#11)
* Banana scan and sample geometries documentation (#9)
* Extended output file (#7)
* CADMesh v2.0.3 (#6)

1.2.0 (2021-04-29)
------------------
* Delete custom binmake file and default to G4INSTALL (#5)
* Add CADMesh functionality back (#4)

1.1.0 (2021-04-21)
------------------
* Major code cleanup (summary in #3)

1.0.0 (2021-04-20)
------------------
(date of GitHub release, original changes summarized on 2019-07-03, for commit 450f026)

* Body of the simulation taken from Dr. Moritz Von Sivers (https://github.com/vonsivers/GeMSE_efficiency_simulation)
* New naming convention for classes
* Upgrade to G4.10.xx versions. Compilation with G4.9.xx no longer compatible
* New Physics list compatible with G4.10.xx and replacement of some outdated references
* Change Makefile structure (include manual config/binmake.gmx)
* Solved detector overlaps (see #1)
* 'ParticleSource' and 'ParticleSourceMessenger' classes introduced, for a more detailed definition of the particles generated, the confinement volumes (possibility of setting various confinements at once) and tracking verbose
* Implementation of the CADMesh feature (and corresponding libraries), in order to load geometries directly from 3D files in the 'GeMSE_DetectorConstruction' class
* Updated RandomSeed definition in RunAction
* Addition of materials and DetectorConstruction cleanup
* Solved visualization conflicts for G4.10.xx
* Added geometries for the various screened samples in the past years (XENONnT material selection campaign, MonXe samples, etc.). Along with that, new structure for the screening samples, separated from the main source code in the folder 'sample_geometries'

