#include "AO.h"


AO::AO()
{
	
}
AO:: AO(string line, MatrixXd ROxhat) {
	readObject(line, ROxhat);
}
void AO::readObject(string line, MatrixXd ROxhat) {
	vector <double> arr;

	//splits the line from spaces into an array of three
	stringstream ssin(line);
	while (ssin.good()) {
		double value;
		ssin >> value;
		arr.push_back(value);
	}
	//Initiate all values

	//assign coordinate values
	//convert string to a long double
	id = arr[0];
	xo = arr[1];
	yo = arr[2];
	zo = arr[3];
	by = ROxhat(0, 0);
	bz = ROxhat(1, 0);
}
void AO::getModel(MatrixXd xyzm) {
		xm = xyzm(0, 0);
		ym = xyzm(0, 1);
		zm = xyzm(0, 2);
		cout << "   xm  " << xm << "   ym  " << ym << "   zm  " << zm << endl;
	
}

void AO::updateXhat(MatrixXd x0) {
	tx = x0(0, 0);
	ty = x0(1, 0);
	tz = x0(2, 0);
	omega = x0(3, 0);
	phi = x0(4, 0);
	kappa = x0(5, 0);
	lamda = x0(6, 0);

	M.resize(3, 3);
	M = rotate(kappa, 3) * rotate(phi, 2) * rotate(omega, 1);
}
void AO::partialAO(int i) {
	
	if (i == 1) {
		Ptx = 1;
		Pty = 0;
		Ptz = 0;
		Pomega = lamda * ym * (-sin(omega) * sin(kappa) + cos(omega) * sin(phi) * cos(kappa))
			+ lamda * zm * (cos(omega) * sin(kappa) + sin(omega) * sin(phi) * cos(kappa));
		Pphi = -lamda * xm * sin(phi) * cos(kappa) + lamda * ym * sin(omega) * cos(phi) * cos(kappa)
			- lamda * zm * cos(omega) * cos(phi) * cos(kappa);
		Pkappa = -lamda * xm * cos(phi) * sin(kappa) + lamda * ym * (cos(omega) * cos(kappa) - sin(omega) * sin(phi) * sin(kappa))
			+ lamda * zm * (sin(omega) * cos(kappa) + cos(omega) * sin(phi) * sin(kappa));
		Plamda = xm * M(0, 0) + ym * M(0, 1) + zm * M(0, 2);
		w = lamda * (M(0, 0) * xm + M(0, 1) * ym + M(0, 2) * zm) + tx - xo;

	}
	else if (i == 2) {
		Ptx = 0;
		Pty = 1;
		Ptz = 0;
		Pomega = lamda * ym * (-sin(omega) * cos(kappa) - cos(omega) * sin(phi) * sin(kappa))
			+ lamda * zm * (cos(omega) * cos(kappa) - sin(omega) * sin(phi) * sin(kappa));
		Pphi = lamda * xm * sin(phi) * sin(kappa) - lamda * ym * sin(omega) * cos(phi) * sin(kappa)
			+ lamda * zm * cos(omega) * cos(phi) * sin(kappa);
		Pkappa = -lamda * xm * cos(phi) * cos(kappa) + lamda * ym * (-cos(omega) * sin(kappa) - sin(omega) * sin(phi) * cos(kappa))
			+ lamda * zm * (-sin(omega) * sin(kappa) + cos(omega) * sin(phi) * cos(kappa));
		Plamda = xm * M(1, 0) + ym * M(1, 1) + zm * M(1, 2);
		w = lamda * (M(1, 0) * xm + M(1, 1) * ym + M(1, 2) * zm) + ty - yo;
	}
	else if (i == 3) {
		Ptx = 0;
		Pty = 0;
		Ptz = 1;
		Pomega = -lamda * ym * cos(omega) * cos(phi) - lamda * zm * sin(omega) * cos(phi);
		Pphi = lamda * xm * cos(phi) + lamda * ym * sin(omega) * sin(phi) - lamda * zm * cos(omega) * sin(phi);
		Pkappa = 0;
		Plamda = xm * M(2, 0) + ym * M(2, 1) + zm * M(2, 2);
		w = lamda * (M(2, 0) * xm + M(2, 1) * ym + M(2, 2) * zm) + tz - zo;
	}
	else {
		cout << "invalid input to derive partial derivatives" << endl;
		exit(1);
	}
}

void AO::transform(MatrixXd xhat) {
	xyzo.resize(3, 1);
	updateXhat(xhat);
	MatrixXd xyzm(3, 1);
	xyzm << xm,
		ym,
		zm;
	MatrixXd t(3, 1);
	t << tx,
		ty,
		tz;
	MatrixXd B(3, 1);
	B << bx,
		by,
		bz;
	xyzo = lamda * M * xyzm + t;

	cout<< id << "    " << xyzo.transpose() << endl;
	//cout <<t.transpose() << endl;
	//cout <<  B.transpose() << endl;
	//cout <<  (lamda*M*B+t).transpose() << endl;
}