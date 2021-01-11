#ifndef CUTEST_CUTEST_H
#define CUTEST_CUTEST_H

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m"

#define CUNIT_OK 0
#define CUNIT_FAIL 1

#define CUTEST_DATA(...) __VA_ARGS__

#define CUTEST_PARAMETRIZE(name, type, ...) \
    type cutest_##name[] = {__VA_ARGS__};               \
    _cutest_parametrize(#name, cutest_##name, sizeof(cutest_##name) / sizeof(type), sizeof(type));

#define CUTEST_GET_PARAMETER(name, type) \
    * (type *) _cutest_get_parameter(name)

#define CUTEST_RUN(test) \
    return _cutest_run(test, #test)

#define CUTEST_ASSERT(cond, msg) \
    if (!(cond)) {                 \
        sprintf(_cutest_error_msg, "Error: %s %s:%d", msg, __FILE__, __LINE__); \
        return CUNIT_FAIL;                             \
    }


void _cutest_parametrize(char* name, void *params, int32_t params_len, int32_t param_size);
uint8_t *_cutest_get_parameter(char *name);
int _cutest_run(int (*test)(), char *name);


#define CUTEST_PARAMS_MAX 16

typedef struct {
    char *name;
    uint8_t *params;
    int32_t params_len;
    int32_t param_size;
} _cutest_param_t;

_cutest_param_t _cutest_params[CUTEST_PARAMS_MAX] = {0};
int32_t _cutest_params_ind[CUTEST_PARAMS_MAX] = {0};

void _cutest_parametrize(char* name, void *params, int32_t params_len, int32_t param_size) {
    int i = 0;
    while(_cutest_params[i].name != NULL) {
        i++;
    }
    _cutest_params[i].name = name;
    _cutest_params[i].params = (uint8_t *) params;
    _cutest_params[i].param_size = param_size;
    _cutest_params[i].params_len = params_len;
}


uint8_t *_cutest_get_parameter(char *name) {
    int i = 0;
    while(strcmp(_cutest_params[i].name, name) != 0) {
        i++;
    }
    return _cutest_params[i].params + _cutest_params_ind[i] * _cutest_params[i].param_size;
}


int _cutest_ok = 0;
int _cutest_failed = 0;
int _cutest_total = 0;
char _cutest_error_msg[1024];


int _cutest_run(int (*test)(), char *name) {
    // Compute the number of params
    int nparams = 0;
    while(_cutest_params[nparams].name != NULL) {
        nparams++;
    }

    // Get the number of iterations
    int niters = 1;
    for (int i = 0; i < nparams; ++i) {
        niters *= _cutest_params[i].params_len;
    }

    // Compute strides
    int32_t params_strides[CUTEST_PARAMS_MAX] = {0};
    params_strides[0] = 1;
    for (int i = 1; i < nparams; ++i) {
        params_strides[i] = params_strides[i - 1] * _cutest_params[i - 1].params_len;
    }

    // Execute parametrization
    char test_name[1024];
    for (int niter = 0; niter < niters; ++niter) {
        sprintf(test_name, "[%d/%d] %s[", niter + 1, niters, name);
        for (int i = 0; i < nparams; ++i) {
            _cutest_params_ind[i] = niter / params_strides[i] % _cutest_params[i].params_len;
            sprintf(test_name, "%s%s%d_", test_name, _cutest_params[i].name, _cutest_params_ind[i]);
        }
        test_name[strlen(test_name) - 1] = 0;
        sprintf(test_name, "%s]", test_name);
        printf("%s ", test_name);

        _cutest_total++;
        int rc = test();
        if (rc == CUNIT_OK) {
            _cutest_ok++;
            fprintf(stdout, GREEN "[OK]\n" RESET);
        } else {
            _cutest_failed++;
            fprintf(stdout, RED "[FAILED]\n" RESET);
        }
        if (_cutest_error_msg[0] != 0) {
            fprintf(stdout, RED "    %s\n" RESET, _cutest_error_msg);
            _cutest_error_msg[0] = 0;
        }
    }

    printf("\nCUTEST RESULTS: %d tests (%d ok, %d failed)\n", _cutest_total, _cutest_ok,
           _cutest_failed);
    return _cutest_failed;
}

#endif //CUTEST_CUTEST_H
