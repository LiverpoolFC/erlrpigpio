#include "erl_nif.h"
#include "erl_gpio.h"
#include "c_gpio.h"

static ErlNifFunc nif_funcs[] =
{
    {"new", 0, erl_gpio_new},
    {"output", 1, erl_gpio_output}
};

static ERL_NIF_TERM erl_gpio_new(ErlNifEnv* env, int argc,
                                   const ERL_NIF_TERM argv[])
{
    gpio_handle* handle = enif_alloc_resource(erl_gpio_RESOURCE,
                                                    sizeof(erl_gpio_handle));
    ERL_NIF_TERM result = enif_make_resource(env, handle);
    enif_release_resource(handle);
    return enif_make_tuple2(env, enif_make_atom(env, "ok"), result);
}


static ERL_NIF_TERM erl_gpio_output(ErlNifEnv* env, int argc,
                                          const ERL_NIF_TERM argv[])
{
    return enif_make_atom(env, "ok");
}

static void erl_gpio_resource_cleanup(ErlNifEnv* env, void* arg)
{
    /* Delete any dynamically allocated memory stored in gpio_handle */
    /* gpio_handle* handle = (gpio_handle*)arg; */
}

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    ErlNifResourceFlags flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
    ErlNifResourceType* rt = enif_open_resource_type(env, NULL,
                                                     "erl_gpio_resource",
                                                     &erl_gpio_resource_cleanup,
                                                     flags, NULL);
    if (rt == NULL)
        return -1;

    erl_gpio_RESOURCE = rt;

    return 0;
}

ERL_NIF_INIT(gpio, nif_funcs, &on_load, NULL, NULL, NULL);
