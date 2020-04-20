all: testxoshiro testocamlrandom testsplitmix

testsplitmix: testsplitmix.c splitmix64.c splitmix64.h
	cc -o $@ $< splitmix64.c

testxoshiro: testxoshiro.c xoshiro256pp.c xoshiro256pp.h
	cc -o $@ $< xoshiro256pp.c

testocamlrandom: testocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c

clean:
	rm -f testxoshiro testocamlrandom testsplitmix

.PHONY: all clean
