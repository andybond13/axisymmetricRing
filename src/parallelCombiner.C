/*******************************************************************************

  Class <parallelCombiner> 

  Author: Andrew Stershic
          Duke Computational Mechanics Lab (DCML)
          Duke University - Durham, NC (USA)
  E-mail: ajs84@duke.edu

  Copyright (c) 2013 Andrew Stershic. All rights reserved. No warranty. No
  liability.

*******************************************************************************/
#include "parallelCombiner.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace boost::filesystem; 

/*******************************************************************************

                M E T H O D S    F O R    R E S O L U T I O N 

*******************************************************************************/

/*------------------------------- P U B L I C --------------------------------*/

ParallelCombiner::ParallelCombiner ()  {}

ParallelCombiner::~ParallelCombiner ()  {}

void ParallelCombiner::run(const int procs, const std::string resultsPath) {

	string vtkPath = resultsPath + "/vtkFiles/";

	//check files for sets
	findSets(vtkPath);

	//combine sets
	std::vector<std::string> inSet;
	combineSet(inSet);

}

/*------------------------------ P R I V A T E -------------------------------*/

void ParallelCombiner::findSets(string inPath) {

	string p = inPath;
	vector<string> allFiles(0);

	//get file listing
	if (is_directory(p)) {
		for (directory_iterator itr(p); itr!=directory_iterator(); ++itr) {
			cout << itr->path().filename() << " "; // display filename only
			if (is_regular_file(itr->status())) {
				cout << " [" << file_size(itr->path()) << "]";
				allFiles.push_back(itr->path().string());
			}
			cout << endl;
		}
	} else {
		cout << (exists(p) ? "Found: " : "Not found: ") << p << endl;
	}

	//check file listing
	for (unsigned i = 0; i < allFiles.size(); ++i) {
		cout << allFiles[i] << endl;
	}

	//sort into sets
	vector<vector<string> > _fileSet(0);
	for (unsigned i = 0; i < allFiles.size(); ++i) {
		vector<string> files(0);
		files.push_back(allFiles[i]);
		for (unsigned i = 0; i < allFiles.size(); ++i) {
			
	
		}

		if (files.size() >= 2) _fileSet.push_back(files);
	}
	


	return;
}

void ParallelCombiner::combineSet(std::vector<std::string> inSet) {}




