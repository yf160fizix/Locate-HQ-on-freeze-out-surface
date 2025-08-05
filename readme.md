# Locate HQ on the freez-out surface

This repository is dedicated to locating heavy quarks in the freeze-out surface using the k-d tree algorithm and writing the associated surface norm vector into a file.

## Files

- `charm.dat`: This file stores the charm list, which is the output of the Lido simulation.
- `surface.dat`: This binary data file stores the freeze-out surface, which is the output of the VISHNEW simulation.
- `nanoflann.hpp`: This is a header-only C++ library for building KD-trees and performing fast nearest-neighbor searches in low-dimensional point clouds. https://github.com/jlblancoc/nanoflann

## Executing program

./run.sh

It generates the data file `charm_with_dsigma_txy.dat`, which includes the components of the surface normal vector in the three columns before the last column.

It also converts the binary data file `surface.dat` to an ASCII text file `text_surface.dat`, which can be read into `visualization_surface.ipynb` for visualization of the freeze-out surface.
