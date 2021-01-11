//
// Created by Aleix Alcacer Sales on 08/01/2021.
//


#include "cutest.h"


typedef struct {
    int ndim;
    int64_t shape[8];
} shape_t;


int simple() {
    CUTEST_GET_PARAMETER(integer, int);
    CUTEST_GET_PARAMETER(string, char *);
    CUTEST_GET_PARAMETER(shape, shape_t);

    if (integer == 2 && shape.ndim != 2) {
        CUTEST_ASSERT(strcmp(string, "HOLA") == 0,
                      "if strings are not equal, print this error");
    }

    return CUNIT_OK;
}


int main() {
    CUTEST_PARAMETRIZE(integer, int, CUTEST_DATA(0, 1, 2, 3));
    CUTEST_PARAMETRIZE(string, char *, CUTEST_DATA("hola", "HOLA"));
    CUTEST_PARAMETRIZE(shape, shape_t, CUTEST_DATA({2, {100, 100}}, {4, {50, 50, 50, 50}}));

    CUTEST_RUN(simple);
}
