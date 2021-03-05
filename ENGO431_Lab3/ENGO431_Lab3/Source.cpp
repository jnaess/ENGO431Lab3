

#include "Point.h"
#include "Model.h"
#include "Functions.h"
#include "LSA.h"

#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




using namespace std;
using namespace Eigen;



int main()
{
    LSA lsa = LSA("Tie_points_corrected.txt");

    lsa.outputModels();

    return 0;
}
