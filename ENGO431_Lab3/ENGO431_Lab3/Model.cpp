#include "Model.h"

Model::Model()
{

}

Model::Model(string line) {
    readLine(line);
}

void Model::readLine(string line) {
    string arr[5];
    int i = 0;

    //splits the line from spaces into an array of three
    stringstream ssin(line);
    while (ssin.good() && i < 5) {
        ssin >> arr[i];
        ++i;
    }
    //Initiate all values

    //assign coordinate values
    //convert string to a long double
    x27 = stold(arr[1]);
    y27 = stold(arr[2]);
    x28 = stold(arr[3]);
    y28 = stold(arr[4]);
}

MatrixXd Model::rotate(double angle, int axis) {
	MatrixXd R(3, 3);
	if (axis == 1) {
		R << 1, 0, 0,
			0, cos(angle), sin(angle),
			0, -sin(angle), cos(angle);
	}
	else if (axis == 2) {
		R << cos(angle), 0, -sin(angle),
			0, 1, 0,
			sin(angle), 0, cos(angle);
	}
	else if (axis == 3) {
		R << cos(angle), sin(angle), 0,
			-sin(angle), cos(angle), 0,
			0, 0 ,1 ;
	}
	else cout << "invalid axis" << endl;
	
	return R;

}

void Model::partial(MatrixXd xo) {
	double by = xo(0,0);
	double bz = xo(1, 0);
	double omega = xo(2, 0);
	double phi = xo(3, 0);
	double kappa = xo(4, 0);
	MatrixXd Ri(3, 1); //Right image (x,y,z)
	Ri << x28,
		y28,
		-c;

	RiT.resize(3,3);
	RiT = rotate(-omega, 1) * rotate(-phi, 2) * rotate(-kappa, 3) * Ri; //Transformed to the left image
	
	double xr = RiT(0, 0);
	double yr = RiT(1, 0);
	double zr = RiT(2, 0);
	
	MatrixXd Mby(3, 3);
	Mby << 0, 1, 0,
		x27, y27, -c,
		xr, yr, zr;
	
	MatrixXd Mbz(3, 3);
	Mbz << 0, 0, 1,
		x27, y27, -c,
		xr, yr, zr;
	MatrixXd Momega(3, 3);
	Momega << bx, by, bz,
		x27, y27, -c,
		0, -zr, yr;
	MatrixXd Mphi(3, 3);
	Mphi << bx, by, bz,
		x27, y27, -c,
		-yr*sin(omega)+zr*cos(omega), xr*sin(omega), -xr*cos(omega);
	MatrixXd Mkappa(3, 3);
	Mkappa << bx, by, bz,
		x27, y27, -c,
		-yr*cos(omega)*cos(phi)-zr*sin(omega)*cos(phi), xr*cos(omega)*cos(phi)-zr*sin(phi), xr*sin(omega)*cos(phi)+yr*sin(phi);
	MatrixXd Mw(3, 3);
	Mw << bx, by, bz,
		x27, y27, -c,
		xr, yr, zr;

	Pby = Mby.determinant();
	Pbz = Mbz.determinant();
	Pomega = Momega.determinant();
	Pphi = Mphi.determinant();
	Pkappa = Mkappa.determinant();
	w = Mw.determinant();
	//cout <<  Pby <<"  "<< Pbz << "  " << Pomega << "  " << Pphi << "  " << Pkappa<< endl;
}
void Model::modelCoord(MatrixXd xhat) {
	double lamda = (bx * RiT(2, 0) - xhat(1, 0) * RiT(0, 0)) / (x27 * RiT(2, 0) + c * RiT(0, 0));
	double mu = (-bx * c - xhat(1, 0) * x27) / (x27 * RiT(2, 0) + c * RiT(0, 0));

	// Compute left/right model coordinates
	xyzm_lr.resize(3,2);
	xyzm_lr(0, 0) = lamda * x27;
	xyzm_lr(1, 0) = lamda * y27;
	xyzm_lr(2, 0) = -lamda * c;
	xyzm_lr(0, 1) = mu * RiT(0, 0) + bx;
	xyzm_lr(1, 1) = mu * RiT(1, 0) + xhat(0,0);
	xyzm_lr(2, 1) = mu * RiT(2, 0) + xhat(1, 0);

	// Calculate y-parallax value
	pY = xyzm_lr(1, 1) - xyzm_lr(1, 0);

	// Calculate merged model coordiantes
	xyzm.resize(1, 3);
	xyzm(0, 0) = xyzm_lr(0, 0);
	xyzm(0, 1) = (xyzm_lr(1, 0) + xyzm_lr(1, 1)) / 2;
	xyzm(0, 2) = xyzm_lr(2, 0);

	cout << endl << "model coordinates" << endl << xyzm << endl;
	cout << "y-parallax" << endl << pY<< endl;
 }

void Model::outputAll() {
    cout << "x27: " << x27 << " y27: " << y27 << " x28: " << x28 << "y28: " << y28 << endl;
}