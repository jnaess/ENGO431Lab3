#pragma once

#include "Functions.h"
#include "Point.h"

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace Eigen;
using namespace std;

class Model {
    double x27, y27, x28, y28;
	double Pby, Pbz, Pomega, Pphi, Pkappa;
	double c = 153.358;
	double bx = 92;
	double by = 0;
	double bz = 0;
	double omega = 0;
	double phi = 0;
	double kappa = 0;

public:

    //Constructor
    Model();

    /*
    Definition:
        Assigns the mesurements via
        a string line that is processed
    Input:
        string line: the file line format: "x27 y27 x28 y28"
    Output:

    */
    Model(string line);


    /*
    Definition:
        Reads in the file line to initialize several class variables
    Input:
        string line: the file line format: "x27 y27 x28 y28"
    Output:

    */
    void readLine(string line);

	/*
   Definition:
	   Returns a rotation matrix about x(1),y(2), or z(3) axis
   Input:
	   rotation angle and axis(1,2,3)
   Output:

   */
	MatrixXd rotate(double angle, int axis);


	void partial();
    /*
    Definition:
        Outputs all values in the model formatted for readablity
    Input:
        
    Output:

    */
    void outputAll();

};