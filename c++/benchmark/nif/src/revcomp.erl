-module(revcomp).

-on_load(init/0).

-export([main/1, string/1, test/0]).

-define(BUFSIZE, 4096).

init() ->
  case code:priv_dir(revcomp) of
    {error, bad_name} ->
      case code:which(?MODULE) of
        Filename when is_list(Filename) ->
          SoName = filename:join([filename:dirname(Filename),"../priv", "revcomp_nifs"]);
        _ ->
          SoName = filename:join("../priv", "revcomp_nifs")
      end;
    Dir ->
      SoName = filename:join(Dir, "revcomp_nifs")
  end,
  erlang:load_nif(SoName, 0).

main(Args) ->
  io:format("args is ~p~n", [Args]),
  Bt = erlang:now(),
  io:setopts([binary]),
  loop(<< >>),
  Et = erlang:now(),
  io:format("time is ~p~n", [timer:now_diff(Et,Bt)]),
  halt().

string(Args) ->
  io:format("args is ~p~n", [Args]),
  %%test_string(),
  halt().

test() ->
  Ret1 = test_string("str123"),
  Ret2 = test_string(<<"bin123">>),
  io:format("~p,~p~n",[Ret1,Ret2]),
  halt().

test_string(_) ->
  exit("NIF library not loaded").

doit(<< >>) ->
  ok;
doit(_Stream) ->
  exit("NIF library not loaded").

loop(Buf) ->
  Line = get_line(),

  case Line of
    eof ->
      io:format("doit ~p~n", [doit(Buf)]);
    << ">", _/bytes >> = Comment ->
      io:format("doit ~p~n", [doit(Buf)]),
      %%doit(Buf),
      io:format("~p~n", [Comment]),
      loop(<< >>);
    Line ->
      %% Strip newline and append.
      %%       S = size(Line) - 1,
      %%       << Chunk:S/bytes, _ >> = Line,
      loop(<< Buf/binary, Line/binary >>)
  end.

get_line() ->
  Buf = case get(linebuf) of
          undefined -> <<>>;
          B -> B
        end,

  %%io:format("buf: ~p~n", [Buf]),
  case binary:split(Buf, <<"\n">>) of
    [Line,Rest] ->
      put(linebuf, Rest),
      Line;
    [_] ->
      IsEOF = get(linebuf_eof) /= undefined,
      if Buf==<<>>, IsEOF ->
          eof;
         true ->
          case file:read(standard_io, ?BUFSIZE) of
            eof ->
              put(linebuf_eof, true),
              get_line();
            {ok, Data} ->
              put(linebuf, <<Buf/binary, Data/binary>>),
              get_line()
          end
      end
  end.

