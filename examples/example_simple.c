//
// Created by Aleix Alcacer Sales on 08/01/2021.
//

#include <cutest.h>
#include <stdio.h>


typedef struct {
    int ndim;
    int64_t shape[8];
} shape_t;


int parametrize() {
    int p1 = CUTEST_GET_PARAMETER("integer", int);
    char *p2 = CUTEST_GET_PARAMETER("string", char *);
    shape_t p3 = CUTEST_GET_PARAMETER("structt", shape_t);

    CUTEST_ASSERT(p1 != 5, "integers are equals");

    return CUNIT_OK;
}


int main() {
    CUTEST_PARAMETRIZE(integer, int, CUTEST_DATA(2, 3, 4, 5, 6, 7))
    CUTEST_PARAMETRIZE(string, char *, CUTEST_DATA("hola", "HOLA"))
    CUTEST_PARAMETRIZE(structt, shape_t, CUTEST_DATA({2, {100, 100}}, {4, {50, 50, 50, 50}}))

    CUTEST_RUN(parametrize);
}
