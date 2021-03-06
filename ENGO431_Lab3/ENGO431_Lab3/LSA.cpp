#include "LSA.h"

LSA::LSA()
{

}


LSA::LSA(string filename)
{
    ifstream file(filename);

    if (file.is_open()) {
        string line;

        //these are used to compare the type of input to read
        int i = 0;

        while (getline(file, line)) {
            //Update the filetype
            //If it switches value then another line needs to be read

            //Only read after line two
            if (i >= 2) {
                //add a new model
                cout << "adding the line: " << line << endl;
                models.emplace_back(line);
                //AddModel(line);
             }

            //increment ot next line
            i++;
        }
        file.close();
    }
}

void LSA::AddModel(string line) {
    models.emplace_back(line);
}



void LSA::designAw() {
	A.resize(models.size(), 5);
	wv.resize(A.rows(),1);
	
	if (counter == 0) {
		xo.resize(5, 1);
		xo.setZero();
	}
		for (unsigned int i = 0; i < A.rows(); i++) {
		models[i].partial(xo);
		A.row(i) << models[i].Pby, models[i].Pbz, models[i].Pomega, models[i].Pphi, models[i].Pkappa;
		wv(i, 0) = models[i].w;
	}
	cout << "design matrix A"<< endl<< A << endl;
	cout << "misclosure" << endl << wv << endl;
}

void LSA::delta() {
	cout << counter << endl;
	MatrixXd delta(5, 1);
	MatrixXd xhat(5, 1);
	MatrixXd N(A.cols(), A.rows());
	N = A.transpose() * A;
	delta = -1*N.inverse() * A.transpose() * wv;
	cout << "delta" <<endl << delta << endl;
	xhat = xo + delta;
	if (abs(delta.maxCoeff()) > 0.00005) {
		xo = xhat;
		counter++;
	}
	else criteria = true;
	cout << "xhat" <<endl<< xhat << endl;

}

void LSA::outputModels() {
    for (int i = 0; i < models.size(); i++) {
        models[i].outputAll();
    }
}

