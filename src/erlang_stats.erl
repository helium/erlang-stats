-module(erlang_stats).

-export([qbeta/3,
         rchisq/1, rchisq/2,
         rpois/1, rpois/2,
         rnorm/2, rnorm/3
        ]).

-define(APPNAME, erlang_stats).
-define(LIBNAME, erlang_stats).

-on_load(init/0).

%%====================================================================
%% API functions
%%====================================================================

qbeta(_Quantile, _A, _B) ->
    not_loaded(?LINE).

rchisq(_DoF) ->
    not_loaded(?LINE).

rchisq(_DoF, _Seed) ->
    not_loaded(?LINE).

rpois(_Rate) ->
    not_loaded(?LINE).

rpois(_Rate, _Seed) ->
    not_loaded(?LINE).

rnorm(_Mean, _Variance) ->
    not_loaded(?LINE).

rnorm(_Mean, _Variance, _Seed) ->
    not_loaded(?LINE).

%%====================================================================
%% Internal functions
%%====================================================================
init() ->
    SoName = case code:priv_dir(?APPNAME) of
        {error, bad_name} ->
            case filelib:is_dir(filename:join(["..", priv])) of
                true ->
                    filename:join(["..", priv, ?LIBNAME]);
                _ ->
                    filename:join([priv, ?LIBNAME])
            end;
        Dir ->
            filename:join(Dir, ?LIBNAME)
    end,
    erlang:load_nif(SoName, 0).

not_loaded(Line) ->
    erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).
