all: testxoshiro testocamlrandom

testxoshiro: testxoshiro.c xoshiro256pp.c xoshiro256pp.h
	cc -o $@ $< xoshiro256pp.c xoshiro256pp.h

testocamlrandom: testocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c ocamlrandom.h

clean:
	rm -f testxoshiro testocamlrandom

.PHONY: all clean
