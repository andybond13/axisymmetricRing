#!/bin/bash

# Go to results directory
cd results

# Remove the data files
cd ./datFiles/; rm *.dat; cd -

# Remove the gnuplot files
cd ./gnuplot/ ; rm *.plt; cd -

# Remove the png files
cd ./pngFiles/; rm *.png; cd -

# Remove the vtk files
cd ./vtkFiles/; rm *.vtk; cd -

# Remove plot.sh
rm plot.sh

# Go back to main directory
cd ..
