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
	//cout << endl << "design matrix A"<< endl<< A << endl;
	//cout << endl << "misclosure" << endl << wv << endl;
}


void LSA::delta() {
	cout << endl << "Iteration count: " << counter << endl;
	MatrixXd delta(m, 1);
	xhat = MatrixXd(m, 1);
	MatrixXd N(A.cols(), A.rows());
	N = A.transpose() * A;
	//cout << endl << "N" << endl << N << endl;
	Cx = N.inverse();
	//cout << endl << "Cx" << endl << Cx << endl;
	//cout << "N inverse" << N.inverse() << endl;
	//HouseholderQR<MatrixXd> qr(N);
	//delta = -qr.solve(A.transpose()*wv);

	delta = -1.0 * N.inverse() * A.transpose() * wv;
	//cout << endl << "delta" <<endl << delta << endl;
	xhat = xo + delta;
	double max = delta.maxCoeff();
	double min = delta.minCoeff();
	if (abs(max) < abs(min))
		max = min;
	//convergence criterion
	if (abs(max) > 0.00001) {
		xo = xhat;
		counter++;
	}
	else {
		criteria = true;
		cout << "Model coordinates of tie points" << endl;
		//cout << "y-parallax of tie" << endl;
		for (unsigned int i = 0; i < A.rows(); i++) {
			models[i].modelCoord(xhat);
		}
		cout << endl << "xhat" << endl << xhat << endl;
	}
	
	

}

void LSA::AOdesignAw() {
	A.resize(controlCoord.size() * 3, 7);
	wv.resize(A.rows(), 1);

	if (counter == 0) {
		xo.resize(7,1);
		xo.setZero();
		xo(5, 0) = atan((controlCoord[1].xo -controlCoord[0].xo) / (controlCoord[1].yo - controlCoord[0].yo))
			- atan((controlCoord[1].xm - controlCoord[0].xm) / (controlCoord[1].ym - controlCoord[0].ym));
		xo(6, 0) = sqrt(pow(controlCoord[1].xo - controlCoord[0].xo, 2) + pow(controlCoord[1].yo - controlCoord[0].yo, 2) + pow(controlCoord[1].zo - controlCoord[0].zo, 2))
			/ sqrt(pow(controlCoord[1].xm - controlCoord[0].xm, 2) + pow(controlCoord[1].ym - controlCoord[0].ym, 2) + pow(controlCoord[1].zm - controlCoord[0].zm, 2));
		cout << "xo is " << endl << xo;
	}
	int point = 1;
	int j = -1;
	for (unsigned int i = 0; i < A.rows(); i++) {
		if (i % 3 == 0) {
			point = 1;
			j++;
		}
		controlCoord[j].updateXhat(xo);
		controlCoord[j].partialAO(point);
		A.row(i) << controlCoord[j].Ptx, controlCoord[j].Pty, controlCoord[j].Ptz, controlCoord[j].Pomega, controlCoord[j].Pphi, controlCoord[j].Pkappa, controlCoord[j].Plamda;
		wv(i, 0) = controlCoord[j].w;
		point++;
	}
	cout << endl << "design matrix A" << endl << A << endl;
	cout << endl << "misclosure" << endl << wv << endl;
}


void LSA::AOdelta() {
	cout << endl << "Iteration count: " << counter << endl;
	MatrixXd delta(7, 1);
	xhat = MatrixXd(7, 1);
	int row = A.rows();
	MatrixXd N(A.cols(), row);
	MatrixXd P;
	P = MatrixXd::Identity(row, row) / pow(stdv, 2);
	//cout << P << endl;

	N = A.transpose() * P * A;
	//cout << endl << "N" << endl << N << endl;
	Cx = N.inverse();
	
	//cout << endl << "Cx" << endl << Cx << endl;
	//cout << "N inverse" << N.inverse() << endl;
	//HouseholderQR<MatrixXd> qr(N);
	//delta = -qr.solve(A.transpose() * P * wv);

	delta = -1.0 * N.inverse() * A.transpose()*P * wv;
	cout << endl << "delta" << endl << delta << endl;
	xhat = xo + delta;
	double max = delta.maxCoeff();
	double min = delta.minCoeff();
	if (abs(max) < abs(min))
		max = min;
	//convergence criterion
	if (abs(max) > 0.00001) {
		xo = xhat;
		counter++;
	}
	else {
		criteria = true;
		v.resize(A.rows(), 1);
		v = wv + A * delta;
		MatrixXd C;
		C = cc();
		//cout << endl << "CC" << endl << C << endl;
		//cout << "transformed obj " << endl;
			//cout << "transformed PC in object space (left) " << endl;
		//cout << "transformed PC in model space (right) " <<  endl;
		//cout << "transformed PC in object space (right) " <<  endl;
		for (unsigned int i = 0; i < controlCoord.size(); i++) {
			controlCoord[i].transform(xhat);
		}
		
		//cout << endl << "residual" << endl << v << endl;
	}
	cout << endl << "xhat" << endl << xhat << endl;
	


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

void LSA::setUpObjectPoints(string filename) {
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



void LSA::getControlPoints(string filename1, string filename2) {
	cout << "Model coordinates of object points" << endl;
	setUpControlPoints(filename1, filename2, xhat);
	for (int i = 0; i < controlCoord.size(); i++) {
		for (int j = 0; j < objectPoints.size(); j++) {
			if (objectPoints[j].id == controlCoord[i].id) {
				objectPoints[j].modelCoord(xhat);
				controlCoord[i].getModel(objectPoints[j].xyzm);
				objectPoints.erase(objectPoints.begin() + j);
			}
		}
	}
	if (objectPoints.size() != 0) {
		for (int i = 0; i < objectCoord.size(); i++) {
			for (int j = 0; j < objectPoints.size(); j++) {
				if (objectPoints[j].id == objectCoord[i].id) {
					objectPoints[j].modelCoord(xhat);
					objectCoord[i].getModel(objectPoints[j].xyzm);
				}
			}
		}
	}
	criteria = false;
	counter = 0;
}

void LSA::setUpControlPoints(string filename1, string filename2, MatrixXd ROxhat) {
	ifstream file1(filename1);
	ifstream file2(filename2);
	if (file1.is_open()) {
		string line;

		//these are used to compare the type of input to read
		int i = 0;

		while (getline(file1, line)) {
			//Update the filetype
			//If it switches value then another line needs to be read

			//Only read after line two
			if (i >= 2) {
				//add a new model
				cout << "adding the line: " << line << endl;
				controlCoord.emplace_back(line,ROxhat);
				//AddModel(line);
			}

			//increment ot next line
			i++;
		}

		file1.close();
	}
	if (file2.is_open()) {
		string line;

		//these are used to compare the type of input to read
		int i = 0;

		while (getline(file2, line)) {
			//Update the filetype
			//If it switches value then another line needs to be read

			//Only read after line two
			if (i >= 2) {
				//add a new model
				cout << "adding the line: " << line << endl;
				objectCoord.emplace_back(line, ROxhat);
				//AddModel(line);
			}

			//increment ot next line
			i++;
		}

		file2.close();
	}
}

void LSA::transform() {
	cout << "transformed obj " << endl;
	for (unsigned int i = 0; i < objectCoord.size(); i++) {
		objectCoord[i].transform(xhat);
	}
}


void LSA::extract() {

	MatrixXd M_r(3, 3);
	MatrixXd M_l(3, 3);
	cout << "RiT is " << endl << models[0].RiT << endl;
	M_l = (controlCoord[0].M).transpose();
	M_r = models[0].RiT * M_l; //MRight = Mim *MLeft
	
	cout << "M right" << endl << M_r << endl;
	cout << "M left" << endl << M_l << endl;

	MatrixXd angleL(1, 3);
	MatrixXd angleR(1, 3);

	angleL(0, 0) = degrees(atan2(-M_l(2, 1), M_l(2, 2)));
	angleL(0, 1) = degrees(asin(M_l(2, 0)));
	angleL(0, 2) = degrees(atan2(-M_l(1, 0), M_l(0, 0)));

	angleR(0, 0) = degrees(atan2(-M_r(2, 1), M_r(2, 2)));
	angleR(0, 1) = degrees(asin(M_r(2, 0)));
	angleR(0, 2) = degrees(atan2(-M_r(1, 0), M_r(0, 0)));

	cout << "Angle right" << endl << angleR << endl;
	cout << "Angle left" << endl << angleL << endl;
}