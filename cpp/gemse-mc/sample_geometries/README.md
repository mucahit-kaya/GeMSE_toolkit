# sample_geometries for the GeMSE_MC

This folder contains examples on different sample shapes and formats to simulate in the GeMSE detector

---

The `*cc` files are written in a way such that you can directly import them in the `GeMSE_DetectorConstruction.cc` class, by doing, e.g.,:
```c++
//_______SAMPLE FROM FILE___________
#include "../sample_geometries/banana_scan.cc"
```

You won't need any headers or shape definitions, since this it not a class per se, but just a code that you effectively copypaste in the construction class.
Remember to compile the code again (`make clean && make`) for the changes to be effective.

---

The `banana_scan.cc` sample is an example on how 3D meshes can be constructed. Notice that the original scans (STL format, in this case) are not included here, in order to keep a reasonable repository size. You can find some STL examples to play with in the `scans_3D` folder.

---

The `txt_format` folder contains examples on how materials and simple shapes can be imported in the code construction via `txt` file. The advantage of this method is that **you do not need to recompile the code afterwards, so you can reuse the same executable for different samples**.

Reference and instructions can be found [here](https://geant4.web.cern.ch/sites/geant4.web.cern.ch/files/geant4/collaboration/working_groups/geometry/docs/textgeom/textgeom.pdf).

For the given example, you can directly run
```bash
$G4WORKDIR/bin/Linux-g++/GeMSE_MC -g sample_geometries/txt_format/test_sample_geometry.txt -m macros/visualization_vrml.mac
```
and you will get an output `wrl` file with the simulated geometry (a cube directly on top of the endcap, made with materials defined in the `txt_format/meteorite_materials.txt` file).
