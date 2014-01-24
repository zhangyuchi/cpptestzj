-module(complex).

-on_load(init/0).

-export([foo/1,bar/1]).

init() ->
    case code:priv_dir(revcomp) of
        {error, bad_name} ->
            case code:which(?MODULE) of
                Filename when is_list(Filename) ->
                    SoName = filename:join([filename:dirname(Filename),"../priv", "complex_nifs"]);
                _ ->
                    SoName = filename:join("../priv", "complex_nifs")
            end;
        Dir ->
            SoName = filename:join(Dir, "complex_nifs")
    end,
    erlang:load_nif(SoName, 0).

foo(_N) ->
    exit("NIF library not loaded").

bar(_N) ->
    exit("NIF library not loaded").
