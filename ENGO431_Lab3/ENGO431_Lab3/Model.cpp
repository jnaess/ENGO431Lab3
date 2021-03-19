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
	id = stold(arr[0]);
    x27 = stold(arr[1]);
    y27 = stold(arr[2]);
    x28 = stold(arr[3]);
    y28 = stold(arr[4]);
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
	RiT = rotate(-omega, 1) * rotate(-phi, 2) * rotate(-kappa, 3);
	Ri = RiT* Ri; //Transformed to the left image
	
	double xr = Ri(0, 0);
	double yr = Ri(1, 0);
	double zr = Ri(2, 0);
	
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
	MatrixXd Ri(3, 1); //Right image (x,y,z)
	Ri << x28,
		y28,
		-c;

	RiT.resize(3, 3);
	RiT = rotate(-xhat(2,0), 1) * rotate(-xhat(3,0), 2) * rotate(-xhat(4,0), 3); //Transformed to the left image
	Ri = RiT * Ri;
	double lamda = (bx * Ri(2, 0) - xhat(1, 0) * Ri(0, 0)) / (x27 * Ri(2, 0) + c * Ri(0, 0));
	double mu = (-bx * c - xhat(1, 0) * x27) / (x27 * Ri(2, 0) + c * Ri(0, 0));

	// Compute left/right model coordinates
	xyzm_lr.resize(3,2);
	xyzm_lr(0, 0) = lamda * x27;
	xyzm_lr(1, 0) = lamda * y27;
	xyzm_lr(2, 0) = -lamda * c;
	xyzm_lr(0, 1) = mu * Ri(0, 0) + bx;
	xyzm_lr(1, 1) = mu * Ri(1, 0) + xhat(0,0);
	xyzm_lr(2, 1) = mu * Ri(2, 0) + xhat(1, 0);
	//cout << "right and left" << endl;
	//cout << xyzm_lr << endl;

	// Calculate y-parallax value
	
	pY = xyzm_lr(1, 1) - xyzm_lr(1, 0);
	//cout << fixed << setprecision(5) <<  pY << endl;

	// Calculate merged model coordiantes
	xyzm.resize(1, 3);
	xyzm(0, 0) = xyzm_lr(0, 0);
	xyzm(0, 1) = (xyzm_lr(1, 0) + xyzm_lr(1, 1)) / 2;
	xyzm(0, 2) = xyzm_lr(2, 0);
	//cout << "kappa   " << xhat(4, 0) << "phi   " << xhat(3, 0) << "omega   " << xhat(2, 0) << endl;
	RiT = rotate(xhat(4, 0), 3) * rotate(xhat(3, 0), 2) * rotate(xhat(2, 0), 1);
	//cout <<"RiT is " <<endl<< RiT << endl;
	cout <<fixed <<setprecision(5) << xyzm << endl;
	
 }




void Model::outputAll() {
    cout << "x27: " << x27 << " y27: " << y27 << " x28: " << x28 << "y28: " << y28 << endl;
}