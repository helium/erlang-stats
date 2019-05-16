-module(erlang_stats).

-export([qbeta/3]).

-define(APPNAME, erlang_sss).
-define(LIBNAME, erlang_sss).

-on_load(init/0).

%%====================================================================
%% API functions
%%====================================================================

qbeta(_Quantile, _A, _B) ->
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
