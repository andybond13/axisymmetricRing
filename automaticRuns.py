# CartRing Automated Runs
# Andrew Stershic - DCML
# ajs84@duke.edu
# 4/17/2013

# Import necessary packages
from subprocess import call
import time
import os

# Get to the right place
os.chdir("/Users/andrewstershic/Code/axisymmetricRing/")

# Clean out old results (if needed)
os.mkdir("results/automatedRuns")
filelist = [ f for f in os.listdir("results/automatedRuns") if f.endswith(".dat") ]
for f in filelist:
    os.remove(f)

# Compile Program
call(["make","clean"])

# Initialize run series information
start = time.clock()
n = 3
series = ""

# Run the series
for x in range(n):
	print ""
	print "Execution number %d" % x
	call(["./bin/main.exe"])
	print fileName
	filelist = [ f for f in os.listdir("results/automatedRuns") if f.endswith(".dat") ]
	for f in filelist:
		fileName = series + f + str(x) + ".dat"
		print fileName
		os.rename(f,fileName)

# Show timing results
elapsed = (time.clock() - start)
print ""
print "Average run-time = ",elapsed/n, " seconds"

# Need to collect and average data
# ...
# minimum fragment size
# size distribution data - average the histogram bins
# cohesive energy 
# fragment count

