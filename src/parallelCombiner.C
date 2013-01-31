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
	for (unsigned i = 0; i < _fileSet.size(); ++i) {
		combineSet(_fileSet[i]);

		//remove unnecessary files
		for (unsigned j = 1; j < _fileSet[i].size(); ++j) {
//			cout << "got here-j" << endl;
			string in2 = _fileSet[i][j];
//			cout << (exists(in2) ? "Found: " : "Not found: ") << in2 << endl;
			remove(in2);
//			cout << (exists(in2) ? "Found: " : "Not found: ") << in2 << endl;
//			cout << endl;
		}
	}

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
	_fileSet.resize(0);
	for (unsigned i = 0; i < allFiles.size()-1; ++i) {
		if (i >= allFiles.size()) return;
		vector<string> files(0);
		files.push_back(allFiles[i]);
		for (unsigned j = i+1; j < allFiles.size(); ++j) {
			if (stringsMatch(allFiles[i],allFiles[j])) {
				files.push_back(allFiles[j]);
				allFiles.erase(allFiles.begin()+j);
				j--;
			}	
		}

		if (files.size() >= 2) {
			_fileSet.push_back(files);
			allFiles.erase(allFiles.begin()+i);
			i--;
		}
	}
	
	//check pairings
	cout << "_fileSet.size() = " << _fileSet.size() << endl;
	for (unsigned i = 0; i < _fileSet.size(); ++i){
		cout << endl;
		for (unsigned j = 0; j < _fileSet[i].size(); ++j){
			cout << _fileSet[i][j] << endl;
		}
	}

	return;
}

void ParallelCombiner::combineSet(std::vector<std::string> inSet) {


	return;
}

bool ParallelCombiner::stringsMatch(std::string in1, std::string in2) {

	//make sure both start with ring and then delete it
	unsigned find1 = in1.find("ring_");
	if (find1 < in1.length()) in1.erase(in1.begin(),in1.begin()+find1+5);
	else return false;
	unsigned find2 = in2.find("ring_");
	if (find2 < in2.length()) in2.erase(in2.begin(),in2.begin()+find2+5);
	else return false;

	//make sure both end with /vtk and then delete it
	find1 = in1.find(".vtk");
	if (find1 < in1.length()) in1.erase(in1.end()-4,in1.end());
	else return false;
	find2 = in2.find(".vtk");
	if (find2 < in2.length()) in2.erase(in2.end()-4,in2.end());
	else return false;
	
	//delete processor number
	find1 = in1.find("_");
	if (find1 < in1.length()) in1.erase(in1.begin(),in1.begin()+find1+1);
	else return false;
	find2 = in2.find("_");
	if (find2 < in2.length()) in2.erase(in2.begin(),in2.begin()+find2+1);
	else return false;

	if (in1==in2) {
		cout << in1 << endl;
		cout << in2 << endl;
		return true;
	}

	return false;
}


