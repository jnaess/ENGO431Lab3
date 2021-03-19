
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
   //LSA ls = LSA("tie_points_corrected.txt");
	LSA ls = LSA("sample.txt");
	
	//ls.setUpObjectPoints("object.txt");
	ls.setUpObjectPoints("sample.txt");


    ls.outputModels();
	while (!ls.criteria) {
		ls.designAw();
		ls.delta();
	}

	//ls.getControlPoints("control.txt","check.txt");
	ls.getControlPoints("AOsample.txt","AOsample.txt");
	while (!ls.criteria) {
		ls.AOdesignAw();
		ls.AOdelta();
	}
	//ls.transform();
	ls.extract();


    return 0;
}
