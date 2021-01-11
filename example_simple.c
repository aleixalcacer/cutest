//
// Created by Aleix Alcacer Sales on 08/01/2021.
//


#include "cutest.h"


int simple() {

    CUTEST_ASSERT(2 != 4, "integers are equals");
    return CUNIT_OK;
}


int main() {
    CUTEST_RUN(simple);
}
