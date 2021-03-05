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

void LSA::outputModels() {
    for (int i = 0; i < models.size(); i++) {
        models[i].outputAll();
    }
}

