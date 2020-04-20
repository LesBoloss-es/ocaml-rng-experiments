all:
	dune build ./testocamlrandom.exe
	dune build ./testxoshiro.exe
	dune build ./bench.exe

bench:
	dune clean
	dune build --profile=release ./bench.exe
	_build/default/bench.exe

clean:
	dune clean

.PHONY: all clean bench
