-module(main).

-export([testcomplex/1, testrevcomp/1, testcomplex_nif/1]).

testcomplex(Args) ->
  io:format("args is ~p~n", [Args]),
  Bt = erlang:now(),
  Init = list_to_integer(hd(Args)),     
  io:setopts([binary]),
  Ret = Init+1,
  Ret1 = Init*2,
  Et = erlang:now(),
  io:format("foo ~p ret = ~p~n", [Init, Ret]),
  io:format("bar ~p ret = ~p~n", [Init, Ret1]),
  io:format("time is ~p~n", [timer:now_diff(Et,Bt)]),
  halt().

testcomplex_nif(Args) -> 
  io:format("args is ~p~n", [Args]),
  Bt = erlang:now(),
  Init = list_to_integer(hd(Args)),     
  io:setopts([binary]),
  Ret = complex:foo(Init),
  Ret1 = complex:bar(Init),
  Et = erlang:now(),
  io:format("foo ~p ret = ~p~n", [Init, Ret]),
  io:format("bar ~p ret = ~p~n", [Init, Ret1]),
  io:format("time is ~p~n", [timer:now_diff(Et,Bt)]),
  halt().


testrevcomp(Args) ->
  io:format("time is ~p, args is ~p~n", [erlang:now(), Args]),
  io:format("time is ~p~n", [erlang:now()]),
  halt().

