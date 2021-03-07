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
	A.resize(models.size(), m);
	wv.resize(A.rows(),1);
	
	if (counter == 0) {
		xo.resize(m, 1);
		xo.setZero();
	}
		for (unsigned int i = 0; i < A.rows(); i++) {
		models[i].partial(xo);
		A.row(i) << models[i].Pby, models[i].Pbz, models[i].Pomega, models[i].Pphi, models[i].Pkappa;
		wv(i, 0) = models[i].w;
	}
	cout << endl << "design matrix A"<< endl<< A << endl;
	cout << endl << "misclosure" << endl << wv << endl;
}


void LSA::delta() {
	cout << endl << "Iteration count: " << counter << endl;
	MatrixXd delta(m, 1);
	xhat = MatrixXd(m, 1);
	MatrixXd N(A.cols(), A.rows());
	N = A.transpose() * A;
	cout << endl << "N" << endl << N << endl;
	Cx = N.inverse();
	cout << endl << "Cx" << endl << Cx << endl;
	//cout << "N inverse" << N.inverse() << endl;
	//HouseholderQR<MatrixXd> qr(N);
	//delta = -qr.solve(A.transpose()*wv);

	delta = -1.0 * N.inverse() * A.transpose() * wv;
	cout << endl << "delta" <<endl << delta << endl;
	xhat = xo + delta;
	if (abs(delta.maxCoeff()) > 0.00001 && counter<4) {
		xo = xhat;
		counter++;
	}
	else {
		criteria = true;
		for (unsigned int i = 0; i < A.rows(); i++) {
			models[i].modelCoord(xhat);
		}

	}
	cout << endl << "xhat" <<endl<< xhat << endl;
	

}

void LSA::outputModels() {
    for (int i = 0; i < models.size(); i++) {
        models[i].outputAll();
    }
}

MatrixXd LSA::cc() {
	int n = Cx.rows();
	C = MatrixXd(n, n);

	for (int i = 0; i < n; i++) {
		for(int j = 0; j < i; j++) {
			C(i, j) = Cx(i, j) / sqrt(Cx(i, i) * Cx(j, j));
			C(j, i) = Cx(i, j) / sqrt(Cx(i, i) * Cx(j, j));
		}
		C(i, i) = 1;
	}

	return C;
}

void LSA::setUpObjectPoint(string filename) {
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
				objectPoints.emplace_back(line);
				//AddModel(line);
			}

			//increment ot next line
			i++;
		}

		file.close();
	}
}

void LSA::getObjectPoints() {
	cout << objectPoints.size() << endl;
	cout << xhat << endl;
	for (int i = 0; i < objectPoints.size(); i++) {
		objectPoints[i].modelCoord(xhat);
	}
}