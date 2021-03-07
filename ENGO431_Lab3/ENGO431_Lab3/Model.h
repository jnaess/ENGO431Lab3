#pragma once

#include "Functions.h"

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


public:
	double Pby, Pbz, Pomega, Pphi, Pkappa;
	double c = 152.15; // sample data
    //double c = 153.358; // our data
	double bx = 92;
	double w =0; //misclosure
	double pY =0;
	MatrixXd RiT;
	MatrixXd xyzm_lr;
    MatrixXd xyzm;
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
		Rotation Matrix

   */
	MatrixXd rotate(double angle, int axis);

	/*
  Definition:
	  Finds partial derivatives of each parameter
  Input:
		
  Output:
		Partial derivatives of by, bz, omega, phi and kappa
  */
	void partial(MatrixXd xo);

	void modelCoord(MatrixXd xhat);
    /*
    Definition:
        Outputs all values in the model formatted for readablity
    Input:
        
    Output:

    */
    void outputAll();

};