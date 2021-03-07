#pragma once
#include <vector>


#include "Model.h"


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

    MatrixXd A, wv, xhat, xo, N, Cx, C; // design matrix, misclosure vector C: correlation coeficianet matrix
    int counter = 0, m = 5;
    vector<Model> models;
    vector<Model> objectPoints;
	bool criteria = false;


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
        Adds a satelites measurement to the vector of measurements
        inside this epoch
    Input:
        The classic satpos.txt line
    Output:

    */
    void AddModel(string line);


	
	void designAw();
	
	void delta();

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
    void setUpObjectPoint(string filename);

    /*
    Definition:
        Gets the model points via the parameters found form the least squares opperation
    Input:
        none, but objectPoints must have been initialized
    Output:

    */
    void getObjectPoints();
};



