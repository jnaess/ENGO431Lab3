#include "LSA.h"

LSA::LSA()
{

}

void LSA::AddModel(string line) {
    models.emplace_back(line);
}

