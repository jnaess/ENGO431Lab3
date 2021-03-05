#include "Model.h"

Model::Model()
{

}

Model::Model(string line) {
    readLine(line);
}

void Model::readLine(string line) {
    string arr[4];
    int i = 0;

    //splits the line from spaces into an array of three
    stringstream ssin(line);
    while (ssin.good() && i < 4) {
        ssin >> arr[i];
        ++i;
    }
    //Initiate all values


    //assign coordinate values
    //convert string to a long double
    x27 = stold(arr[0]);
    y27 = stold(arr[1]);
    x28 = stold(arr[2]);
    y28 = stold(arr[3]);
}