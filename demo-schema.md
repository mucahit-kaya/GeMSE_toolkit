``` bash
schema_version: 1.0
input:
  sample_root: path/to/sample.root
  background_root: path/to/bg.root
calibration: path/to/calib.root
resolution: path/to/resolution.root
activity:
  bayes_factor_threshold: 0.33
  cl: 0.95
simulation:
  macro: macros/efficiency_standard_isotopes_G4103p3.mac
  geometry: sample.txt
output_dir: out/

```
