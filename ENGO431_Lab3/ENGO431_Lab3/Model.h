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
        Outputs all values in the model formatted for readablity
    Input:
        
    Output:

    */
    void outputAll();
};