all: tests bench

tests:
	dune build ./tests/ocamlrandom.exe
	dune build ./tests/xoshiro.exe
	dune build ./tests/splitmix.exe

bench:
	dune build ./bench.exe

clean:
	dune clean

.PHONY: all clean bench tests
