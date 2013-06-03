#!/bin/bash

# Go to results directory
cd /Users/andrewstershic/Code/axisymmetricRing/results

# Remove the data files
cd ./datFiles/; rm *.dat; cd -

cd ./automatedRuns/; rm *.dat; cd -

# Remove the gnuplot files
cd ./gnuplot/ ; rm *.plt; cd -

# Remove the png/svg files
cd ./pngFiles/; rm *.png; cd -

cd ./pngFiles/; rm *.svg; cd -

# Remove the vtk files
cd ./vtkFiles/; find . -name "*.vtk" -print0 | xargs -0 rm -f; cd -

# Remove plot.sh
rm plot.sh
