# Locate HQ on the freez-out surface

This repository is dedicated to locating heavy quarks in the freeze-out surface using the k-d tree algorithm and writing the associated surface norm vector into a file.

## Files

- `charm.dat`: This file stores the charm list, which is the output of the Lido simulation.
- `surface.dat`: This binary data file stores the freeze-out surface, which is the output of the VISHNEW simulation.
- `nanoflann.hpp`: This is a header-only C++ library for building KD-trees and performing fast nearest-neighbor searches in low-dimensional point clouds. https://github.com/jlblancoc/nanoflann 
