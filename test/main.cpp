/*******************************************************************************

  Class <CartRing> 

  Author: Martin Hautefeuille
          Duke Computational Mechanics Lab (DCML)
          Duke University - Durham, NC (USA)
  E-mail: mh186@duke.edu

  Copyright (c) 2010 Martin Hautefeuille. All rights reserved. No warranty. No
  liability.

*******************************************************************************/
#include "cartRing.h"
#include <iostream>
#include <math.h>
#include "matPropGen.h"
//#include "mpi.h"

using namespace std;

int main () {

    // ring specification
    double L   = .05;   // in m
    double A   = 1.0e-6;   // in m^2
    double rho = 2.75e+3;  // in kg/m3
    double E   = 2.75e+11; // in Pa
    int nx     = 20;
//    std::string path = "/home/ajs84/Software/cartRing/results";
//    std::string path = "~/andrew/Duke/results";
	std::string path = "/Users/andrewstershic/Code/axisymmetricRing/results";

    CartRing ring( L, A, rho, E, nx, path );

	//ring.applyForc( "CONS", "THETA", 6.0e-1 );
    //ring.initVel( "RADIA", 2.5*1.592e+1 );
    //ring.applyForc( "LINE", "RADIA", 1.592e+1 );
    //ring.applyForc( "CONS", "RADIA", 6.0e-1 );
    ring.applyVel( "RADIA", 4.5*1.592e+1);

    // cohesive law
    /**/
    std::vector<std::vector<double> > cohPar( 2 );
    /*cohPar[0].assign( nx, 4.0e+12 ); //4.0e+12
    cohPar[0][nx-100] = 4.4e+9;
    cohPar[0][nx-125] = 4.37e+9;
    cohPar[0][nx-150] = 4.37e+9;
    cohPar[0][nx-525] = 4.4e+9;*/

    std::vector<unsigned> cohNums(4);
    cohNums[0] = 41; cohNums[1] = 92; cohNums[2] = 99; cohNums[3] = 107;
    std::string distrib = "Normal";
    double param1 = 3e+8; 	//4.37785e+8;		//Theoretically stress_max = v0*sqrt(E*rho)
    double param2 = 0;
    double param3 = 0;

    MatPropGen properties(distrib, param1, param2, param3, nx);
    properties.assign(cohPar[0], cohNums);
    cohPar[1].assign( 1, 100 );
    ring.setCohLaw( "LINSG", cohPar );
    ring.plotCohLaw( cohNums );
    

    ring.display( 10, 10 );

    unsigned nodes[] = { 0, 1 };
    std::vector<unsigned> node2plot ( nodes, nodes+2 );
    ring.plotAtNodes( node2plot );

    unsigned elm[] = { 0, 1 };
    std::vector<unsigned> elm2plot ( elm, elm+2 );
    ring.plotAtElms( elm2plot );

    ring.plotEnergies();
    ring.plotFrags();
    ring.plotSTheta();
    ring.defectLimit(0.02);



    double totalTime = 5.0e-06;
    unsigned printFreq = 1;
    double refine = 0.2;
	ring.solve( totalTime, printFreq, refine );
    ring.printHisto();
    double runTime; unsigned numFrag; unsigned nIter; double Wcoh0; double Wsum; double Wmax; double WsprD;
    std::vector<double> fragLength; double meanFragLength; std::vector<unsigned> fHisto;
    std::vector<std::vector<double> >fragInvCDF;
    ring.grabInfo( runTime, numFrag, nIter, Wcoh0, Wsum, Wmax, fragLength, meanFragLength, WsprD, fHisto, fragInvCDF);

    std::cout << "runtime: " << runTime << "   numFrag: " << numFrag << " nIter: " << nIter << std::endl;

    return 0;
}

