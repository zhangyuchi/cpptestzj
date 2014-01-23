c:
gcc -pipe -Wall -O3 -fomit-frame-pointer -std=c99 -pthread revcomp.c -o revcomp.exe
./revcomp.exe 0 < revcomp-input.txt

erlang:
erlc +native +"{hipe, [o3]}"  revcomp.erl
erl -smp disable -noshell -run  revcomp main 0 < revcomp-input.txt
