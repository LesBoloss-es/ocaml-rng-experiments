all: tests bench

test:
	dune test

bench:
	dune build ./bench.exe

clean:
	dune clean

.PHONY: all clean bench test
