#pragma once
#include <vector>


#include "Model.h"
#include "AO.h"
#include "Functions.h"

#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace Eigen;
using namespace std;

class LSA {
	
public:

    MatrixXd A, wv, xhat, xo, N, Cx, C, v; // design matrix, misclosure vector C: correlation coeficianet matrix
    int counter = 0, m = 5; //counts number of iterations and m is number of unknown parameters
    vector<Model> models;
    vector<Model> objectPoints;
	vector<AO> controlCoord;
	vector<AO> objectCoord;
	double stdv = 0.003;
	bool criteria = false; //check if correction vector meets the criterion


    //Constructor
    LSA();

    /*
    Definition:
        Contructs the vector of models by iterated line by line through the file
        Skips the first two lines
    Input:
        string filename

    Output:

    */
    LSA(string filename);

    /*
    Definition:
        Adds a image coordinates of left and right images
    Input:
        The classic tie_points_corrected.txt line
    Output:

    */
    void AddModel(string line);

	/*
  Definition:
	  Builds design matrix A and misclosure vector
  Input:
	  
  Output: Updates design matrix A(A), misclosure vector(wv)

  */
	void designAw();
	
	/*
Definition:
	Finds correction vector, delta and estimates unknown parameters
Input:

Output: Updates delta, xhat

*/
	void delta();

	void AOdesignAw();
	void AOdelta();
	
    /*
    Definition:
        Iterates through the vector of models and outputs all values
    Input:
        
    Output:

    */
    void outputModels();

    /*
    Definition:
        Initialized the correlation coefficient matrix
        Cx  must be initialized beforehand
    Input:

    Output:
        MatrixXd correlation coeficient
    */
    MatrixXd cc();

    /*
    Definition:
        After the least squares opperation is done use this functions to initialize the odjectpoint vector
    Input:
        string filename of the oject points
    Output:
        
    */
	void setUpObjectPoints(string filename);

    /*
    Definition:
        Gets the model points via the parameters found form the least squares opperation and setting up for absolute orientation
    Input:
         string filename of the control points(filename1), oject points(filename2) in the object space
    Output:

    */
    void getControlPoints(string filename1,string filename2);


	/*
	Definition:
	  After relative Orientation is done use this functions to initialize the odjectpoint vector
  Input:
	  string filename of the control points(filename1), oject points(filename2) in the object space, RO parameters
  Output:

  */
	void setUpControlPoints(string filename1, string filename2, MatrixXd ROxhat);

	/*
	Definition:
	  After absolute Orientation is done use this functions to transform the object coordinates
  Input:
	
  Output: transformed object coordinates and principal point 

  */
	void transform();

	/*
	Definition:
	  Extract the rotation angles 
  Input:

  Output:
		rotation angles of both left and right images

  */
	void extract();
};



