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
void Model::partial() {
	MatrixXd Ri(3, 1); //Right image (x,y,z)
	Ri << x28,
		y28,
		0;
	MatrixXd RiT = rotate(-omega, 1) * rotate(-phi, 2) * rotate(-kappa, 3) * Ri; //Transformed to the left image
	double xr = RiT(0, 0);
	double yr = RiT(1, 0);
	double zr = RiT(2, 0);
	MatrixXd Mby(3, 3);
	Mby << 0, 1, 0,
		x27, y27, -c,
		xr, yr, zr;
	MatrixXd Mbz(3, 3);
	Mby << 0, 0, 1,
		x27, y27, -c,
		xr, yr, zr;
	MatrixXd Momega(3, 3);
	Mby << bx, by, bz,
		x27, y27, -c,
		0, -zr, yr;
	MatrixXd Mphi(3, 3);
	Mby << bx, by, bz,
		x27, y27, -c,
		-yr*sin(omega)+zr*cos(omega), xr*sin(omega), -xr*cos(omega);
	MatrixXd Mkappa(3, 3);
	Mby << bx, by, bz,
		x27, y27, -c,
		-yr*cos(omega)*cos(phi)-zr*sin(omega)*cos(phi), xr*cos(omega)*cos(phi)-zr*sin(phi), xr*sin(omega)*cos(phi)+yr*sin(phi);

	Pby = Mby.determinant();
	Pbz = Mbz.determinant();
	Pomega = Momega.determinant();
	Pphi = Mphi.determinant();
	Pkappa = Mkappa.determinant();
}

void Model::outputAll() {
    cout << "x27: " << x27 << " y27: " << y27 << " x28: " << x28 << "y28: " << y28 << endl;
}