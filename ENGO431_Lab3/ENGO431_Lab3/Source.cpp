

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
    LSA ls = LSA("Tie_points_corrected.txt");
	//LSA ls = LSA("sample.txt");
	//LSA ls = LSA("object.txt");

    ls.outputModels();
	while (!ls.criteria) {
		ls.designAw();
		ls.delta();
	}
	
	cout << endl << "Correlation matrix cc" << endl << ls.cc();
    return 0;
}
