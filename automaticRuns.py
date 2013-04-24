# CartRing Automated Runs
# Andrew Stershic - DCML
# ajs84@duke.edu
# 4/17/2013

# Import necessary packages
from subprocess import call
import time
import os

# Get to the right place
call(["clear"])
os.chdir("/Users/andrewstershic/Code/axisymmetricRing/")

# Clean out old results (if needed)
if not os.path.exists("results/automatedRuns"):
    os.makedirs("results/automatedRuns")
filelist = [ f for f in os.listdir("results/automatedRuns") if f.endswith(".dat") ]
for f in filelist:
    os.remove("results/automatedRuns/" + f)

# Compile Program
call(["make","clean"])
call(["make"])

# Initialize run series information
#start = time.clock()
startT = time.time()
n = 10
series = ""
p = 4

# Run the series
for x in range(n):
	print ""
	print "Execution number %d" % x
	if (p == 1):
		call(["./bin/main.exe"])
	else:
		call(["mpirun","-np",str(p),"./bin/main.exe"])
	filelist = [ f for f in os.listdir("results/datFiles") if f.endswith(".dat") ]
	for f in filelist:
		f_raw = f.replace(".dat","")
		fileName = "results/automatedRuns/" + series + f_raw + "-" + str(x)  + ".dat"
		print fileName
		os.rename("results/datFiles/"+f,fileName)

# Show timing results
#elapsed = (time.clock() - start)
elapsedT = (time.time() - startT)
print ""
#print "Average run-time = ",elapsed/n, " seconds"
print "Average run-time = ",elapsedT/n, " seconds"

# Need to collect and average data
# ...
# minimum fragment size
# size distribution data - average the histogram bins
# cohesive energy 
# fragment count

