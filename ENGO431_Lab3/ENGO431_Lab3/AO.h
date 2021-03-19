#pragma once
#include "Functions.h"

class AO {


public:
	double id, xm, ym, zm, xo, yo, zo, Pby, Pbz, Pomega, Pphi, Pkappa, by, bz;
	double Ptx = 0, Pty = 0, Ptz = 0, Plamda=0;
	double c = 152.15; // sample data
	//double c = 153.358; // our data
	MatrixXd M, xyzo;
	double w = 0;
	double bx = 92; //misclosure
	double tx, ty, tz, imega, phi, kappa, omega, lamda;

	//Constructor
	AO();

	/*
Definition:
	Contructs the vector of models by iterated line by line through the file
	Skips the first two lines by calling readObject
Input:
	string filename and RO parameters

Output:

*/
	AO(string line, MatrixXd ROxhat);

	/*
Definition:
	Contructs the vector of models by iterated line by line through the file
	Skips the first two lines
Input:
	string filename and RO parameters

Output:

*/
	void readObject(string line, MatrixXd ROxhat);

	/*
Definition:
	Assgin model coordinates to the meeber variables

Input:
	Model coordinates, xyzm 

Output:

*/
	void getModel(MatrixXd xyzm);

	/*
Definition:
	Update the esimated parameters for iteration
Input:
	Estimated parameters

Output:

*/
	void updateXhat(MatrixXd x0);

	/*
Definition:
	Derive the partial derivatives t

Input:
	Model coordinates, xyzm

Output:

*/
	void partialAO(int i);

	/*
Definition:
  After absolute Orientation is done use this functions to transform the object coordinates
Input:

Output: transformed object coordinates and principal point

*/
	void transform(MatrixXd xhat);
		

}; 