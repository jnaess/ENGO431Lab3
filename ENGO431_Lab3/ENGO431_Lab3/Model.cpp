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

void Model::outputAll() {
    cout << "x27: " << x27 << " y27: " << y27 << " x28: " << x28 << "y28: " << y28 << endl;
}