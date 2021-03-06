/*
 * Copyright 2018 Helium Systems Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "erl_nif.h"
#include "stats/include/stats.hpp"
#include <string.h>

static ERL_NIF_TERM
qbeta(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[])
{
    double quantile, a, b;
    if (argc != 3 ||
            !enif_get_double(env, argv[0], &quantile) ||
            !enif_get_double(env, argv[1], &a) ||
            !enif_get_double(env, argv[2], &b)) {
        return enif_make_badarg(env);
    }
    double result = stats::qbeta(quantile, a, b);
    return enif_make_double(env, result);
}

static ErlNifFunc nif_funcs[] =
    {{"qbeta", 3, qbeta, 0}};

#define ATOM(Id, Value)                                                        \
    {                                                                          \
        Id = enif_make_atom(env, Value);                                       \
    }

static int
load(ErlNifEnv * env, void ** priv_data, ERL_NIF_TERM load_info)
{
    (void)priv_data;
    (void)load_info;
    (void)env;

    return 0;
}

ERL_NIF_INIT(erlang_stats, nif_funcs, load, NULL, NULL, NULL);

