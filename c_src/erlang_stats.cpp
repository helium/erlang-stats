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
#include <random>

static std::mt19937_64 rng;

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

static ERL_NIF_TERM
rchisq(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[])
{
    unsigned int dof;
    if (argc >= 1 && argc < 3 && enif_get_uint(env, argv[0], &dof)) {
        if (argc == 2) {
            unsigned int seed;
            if (enif_get_uint(env, argv[1], &seed)) {
                unsigned int result = stats::rchisq(dof, seed);
                return enif_make_uint(env, result);
            } else {
                return enif_make_badarg(env);
            }
        } else {
            unsigned int result = stats::rchisq(dof, rng);
            return enif_make_uint(env, result);
        }
    } else {
        return enif_make_badarg(env);
    }
}

static ErlNifFunc nif_funcs[] =
    {
        {"qbeta", 3, qbeta, 0},
        {"rchisq", 1, rchisq, 0},
        {"rchisq", 2, rchisq, 0}
    };

#define ATOM(Id, Value)                                                        \
    {                                                                          \
        Id = enif_make_atom(env, Value);                                       \
    }

static int
load(ErlNifEnv * env, void ** priv_data, ERL_NIF_TERM load_info)
{
    rng.seed(time(0));
    (void)priv_data;
    (void)load_info;
    (void)env;

    return 0;
}

ERL_NIF_INIT(erlang_stats, nif_funcs, load, NULL, NULL, NULL);

