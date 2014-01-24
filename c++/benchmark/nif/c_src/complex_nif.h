#ifndef INCL_COMPLEX_NIF_H
#define INCL_COMPLEX_NIF_H

extern "C" {

#include "erl_nif.h"

// Prototypes
    ERL_NIF_TERM foo_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
    ERL_NIF_TERM bar_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
}

#endif
