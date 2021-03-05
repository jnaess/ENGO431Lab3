#pragma once
#include <vector>

#include "Point.h"
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
    vector<Model> models;

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

    /*
    Definition:
        Iterates through the vector of models and outputs all values
    Input:
        
    Output:

    */
    void outputModels();
};



