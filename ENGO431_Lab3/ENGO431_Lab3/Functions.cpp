#include "Functions.h"


void TestPrint(MatrixXd M, string title) {
    //Print the title of this matrix
    cout << "___" << title << "___" << endl;
    cout << M << endl;
    cout << endl;
}

double degrees(double deg, double min, double sec) {
    return deg + min / 60 + sec / 3600;
}

vector<double> dms(double degrees) {
    vector<double> dms;

    int deg = degrees;

    //truncate degrees
    dms.push_back(deg);

    //truncate arc minutes
    degrees = (degrees - double(deg)) * 60;
    deg = degrees;
    dms.push_back(deg);

    //arc seconds does not need to be concatenated
    degrees = (degrees - double(deg)) * 60;
    dms.push_back(degrees);

    return dms;
}

double degrees(double rad) {
    double PI = acos(-1);

    return rad * (180 / PI);
}

void Output(string filename, MatrixXd m) {
    //Output file
    ofstream out(filename);
    if (out.fail())
    {
        cout << "Could not open output file" << endl;
        exit(1);
    }
    out << filename << endl;
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            out << setw(6) << fixed << setprecision(6) << m(i, j) << "   ";
        }
        out << endl;
    }
    return;
}

double radians(double deg) {
    double PI = acos(-1);

    return deg * PI / 180;
}

MatrixXd rotate(double angle, int axis) {
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
			0, 0, 1;
	}
	else cout << "invalid axis" << endl;

	return R;

}

void print_mat(MatrixXd mat, string name)
{
    cout << "\n" << name << "\n";
    for (int i = 0; i < mat.rows(); ++i)
    {
        for (int j = 0; j < mat.cols(); ++j)
        {
            cout << mat(i, j) << "  ";
        }
        cout << "\n";
    }
}