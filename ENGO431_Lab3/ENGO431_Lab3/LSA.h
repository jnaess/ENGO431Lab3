#pragma once

#include "Point.h"
#include "Model.h"
#include "LSA.h"

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace Eigen;
using namespace std;

class LSA {
    vector<Model> models;

public:

    //Constructor
    LSA();

    /*
    Definition:
        Adds a satelites measurement to the vector of measurements
        inside this epoch
    Input:
        The classic satpos.txt line
    Output:

    */
    void AddModel(string line);
}



