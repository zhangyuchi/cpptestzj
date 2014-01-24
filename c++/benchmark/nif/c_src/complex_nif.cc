#include "complex_nif.h"

extern unsigned long foo(unsigned long x);
extern unsigned long bar(unsigned long y);

// Atoms (initialized in on_load)
static ERL_NIF_TERM ATOM_TRUE;
static ERL_NIF_TERM ATOM_OK;
static ERL_NIF_TERM ATOM_ERROR;

static ErlNifFunc nif_funcs[] = {
    {"foo", 1, foo_nif},
    {"bar", 1, bar_nif}
};

template <typename Acc> ERL_NIF_TERM fold(ErlNifEnv* env, ERL_NIF_TERM list,
                                          ERL_NIF_TERM(*fun)(ErlNifEnv*, ERL_NIF_TERM, Acc&),
                                          Acc& acc)
{
    ERL_NIF_TERM head, tail = list;
    while (enif_get_list_cell(env, tail, &head, &tail))
    {
        ERL_NIF_TERM result = fun(env, head, acc);
        if (result != ATOM_OK)
        {
            return result;
        }
    }

    return ATOM_OK;
}


ERL_NIF_TERM foo_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    unsigned long ret;
    unsigned long x;
    if (!enif_get_ulong(env, argv[0], &x)) {
	return enif_make_badarg(env);
    }
    ret = foo(x);
    ERL_NIF_TERM value = enif_make_ulong(env, ret);
    //return enif_make_tuple2(env, ATOM_OK, value);
    //return enif_make_int(env, ret);
    return value;
    //return ATOM_OK;
}

ERL_NIF_TERM bar_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    unsigned long y, ret;
    if (!enif_get_ulong(env, argv[0], &y)) {
	return enif_make_badarg(env);
    }
    ret = bar(y);
    ERL_NIF_TERM value = enif_make_ulong(env, ret);
    //return enif_make_tuple2(env, ATOM_OK, value);
    //return enif_make_tuple2(env, "ok", ret);
    //return enif_make_int(env, ret);
    return value;
}

#define ATOM(Id, Value) { Id = enif_make_atom(env, Value); }

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    // Initialize common atoms
    ATOM(ATOM_OK, "ok");
    ATOM(ATOM_ERROR, "error");
    ATOM(ATOM_TRUE, "true");

    return 0;
}

extern "C" {
    ERL_NIF_INIT(complex, nif_funcs, &on_load, NULL, NULL, NULL)
}
