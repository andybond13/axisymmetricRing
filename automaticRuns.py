# CartRing Automated Runs
# Andrew Stershic - DCML
# ajs84@duke.edu
# 4/17/2013

# Import necessary packages
from subprocess import call
import time
import os

# Define tail function which will return the last 'window' lines
def tail( fh, window=1 ):
	with open(fh, 'r') as f: 
		BUFSIZ = 1024
		f.seek(0, 2)
		bytes = f.tell()
		size = window
		block = -1
		data = []
		while size > 0 and bytes > 0:
		    if (bytes - BUFSIZ > 0):
		        # Seek back one whole BUFSIZ
		        f.seek(block*BUFSIZ, 2)
		        # read BUFFER
		        data.append(f.read(BUFSIZ))
		    else:
		        # file too small, start from begining
		        f.seek(0,0)
		        # only read what was not read
		        data.append(f.read(bytes))
		    linesFound = data[-1].count('\n')
		    size -= linesFound
		    bytes -= BUFSIZ
		    block -= 1
		return '\n'.join(''.join(data).splitlines()[-window:])


# --------------------------------
# Main function

# Get to the right place
base = "/Users/andrewstershic/Code/axisymmetricRing/"
call(["clear"])
os.chdir(base)

# Clean out old results (if needed)
if not os.path.exists("results/automatedRuns"):
    os.makedirs("results/automatedRuns")
filelist = [ f for f in os.listdir("results/automatedRuns") if f.endswith(".dat") ]
for f in filelist:
    os.remove("results/automatedRuns/" + f)

# Compile Program
#call(["make","clean"])
call(["make"])

# Initialize run series information
#start = time.clock()
startT = time.time()
n = 2
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
min_frag_size = 0
num_frags = 0
for x in range(n):
	f = "results/automatedRuns/fraginfo-" + str(x) + ".dat"
#	f = os.popen("results/automatedRuns/fraginfo-" + str(x) + ".dat")
	line = tail(f,1)
	line = line.split()
	min_frag_size += float(line[6])/n
	num_frags += float(line[1])/n

print 'Average minimum fragment size = ', min_frag_size
print 'Average number of fragments = ', num_frags

# ...
# minimum fragment size
# size distribution data - average the histogram bins
# cohesive energy 
# fragment count

