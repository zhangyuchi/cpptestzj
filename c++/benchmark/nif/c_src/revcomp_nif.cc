#include <cstdio>
#include <cstring>
#include "revcomp_nif.h"

extern int doit(char* buf, size_t buf_len);

// Atoms (initialized in on_load)
static ERL_NIF_TERM ATOM_TRUE;
static ERL_NIF_TERM ATOM_OK;
static ERL_NIF_TERM ATOM_ERROR;

static ErlNifFunc nif_funcs[] = {
    {"doit", 1, doit_nif},
    {"test_string", 1, test_string},
    {"test_pid", 1, test_pid}
};

template <typename Acc> ERL_NIF_TERM fold(ErlNifEnv* env, ERL_NIF_TERM list,
                                          ERL_NIF_TERM(*fun)(ErlNifEnv*, ERL_NIF_TERM, Acc&),
                                          Acc& acc)
{
    ERL_NIF_TERM head, tail = list;
    while (enif_get_list_cell(env, tail, &head, &tail)) {
        ERL_NIF_TERM result = fun(env, head, acc);
        if (result != ATOM_OK) {
            return result;
        }
    }
    return ATOM_OK;
}

ERL_NIF_TERM test_string(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    char name[4096];    
    if (enif_get_string(env, argv[0], name, sizeof(name), ERL_NIF_LATIN1))
    {
        ErlNifBinary reply;
        enif_inspect_iolist_as_binary(env, argv[0], &reply);
        //return enif_make_string(env, name, ERL_NIF_LATIN1);
        return enif_make_binary(env, &reply);
    }
    else if (enif_is_binary(env, argv[0]))
    {
        ErlNifBinary orig_bin;
        //enif_inspect_binary(env, argv[0], &reply);//from term get binary 
        if (!enif_inspect_binary(env, argv[0], &orig_bin))
            return enif_make_badarg(env);

        unsigned char* orig_buf = orig_bin.data;
        size_t orig_len = orig_bin.size;

        strcpy((char *)orig_buf, "zj11111111111111111111111111111111111111111111111111111111111111111111111111111");

        ERL_NIF_TERM value;
        ERL_NIF_TERM ret;
        
        unsigned char *buf = enif_make_new_binary(env, 10, &value);//set a binary,interface is buf
        strncpy((char *)buf, "hello", 5);
        //return enif_make_binary(env, &reply);
        //return value;
        ret = enif_make_int(env,orig_len);
        return enif_make_tuple3(env, ret, argv[0], enif_make_binary(env, &orig_bin));
    }
    else 
    {
        return enif_make_badarg(env);
    }
}

struct thread_ctx
{
    ErlNifPid to_pid;
    ErlNifEnv* to_env;
};

void* thread_run(void *arg) 
{
    thread_ctx* ctx = (thread_ctx *)arg;

    enif_send(NULL, &ctx->to_pid, ctx->to_env, enif_make_tuple2(ctx->to_env, ATOM_OK, enif_make_int(ctx->to_env,0)));
    enif_free_env(ctx->to_env);
    return NULL;
}

ERL_NIF_TERM test_pid(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    char name[4096];

    printf("test_pid env is %p\n", env);

    if (enif_is_pid(env, argv[0]))
    {
        thread_ctx* ctx = (thread_ctx *)malloc(sizeof(thread_ctx));

        //enif_get_local_pid(env, argv[0], &(ctx->to_pid));
        enif_self(env, &ctx->to_pid);
        ErlNifEnv* myenv = enif_alloc_env();
        ctx->to_env = myenv;//(ErlNifEnv *)enif_priv_data();
        
        ErlNifTid tid;
        enif_thread_create("loop", &tid, thread_run, ctx, NULL);

        //return enif_make_string(env, name, ERL_NIF_LATIN1);
        return enif_make_tuple2(env, ATOM_OK, argv[0]);
    }
    else 
    {
        return enif_make_badarg(env);
    }
}

ERL_NIF_TERM doit_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    if (enif_is_binary(env, argv[0]))
    {
        int ret=0;
        ErlNifBinary orig_bin;
        if (!enif_inspect_binary(env, argv[0], &orig_bin))
            return enif_make_badarg(env);

        unsigned char* orig_buf = orig_bin.data;
        size_t orig_len = orig_bin.size;
        
        ret = doit((char *)orig_buf, orig_len);

        ERL_NIF_TERM value;
        value = enif_make_int(env, ret);
        return value;
    }
    
    return enif_make_badarg(env);
}

#define ATOM(Id, Value) { Id = enif_make_atom(env, Value); }

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    // Initialize common atoms
    ATOM(ATOM_OK, "ok");
    ATOM(ATOM_ERROR, "error");
    ATOM(ATOM_TRUE, "true");

    //ErlNifEnv* myenv = enif_alloc_env();
    //*priv_data = (void *)myenv;

    printf("load env is %p\n", env);

    return 0;
}

extern "C" {
    ERL_NIF_INIT(revcomp, nif_funcs, &on_load, NULL, NULL, NULL)
}

