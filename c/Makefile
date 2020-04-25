BIN =\
		 testxoshiro\
		 testsplitmix\
		 testocamlrandom\
		 testu01ocamlrandom\
		 testu01xoshiro

all: $(BIN)

testsplitmix: testsplitmix.c splitmix64.c splitmix64.h
	cc -o $@ $< splitmix64.c

testxoshiro: testxoshiro.c xoshiro256pp.c xoshiro256pp.h
	cc -o $@ $< xoshiro256pp.c

testu01xoshiro: testu01xoshiro.c xoshiro256pp.c xoshiro256pp.h
	cc -o $@ $< xoshiro256pp.c -ltestu01

testocamlrandom: testocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c -ltestu01

testu01ocamlrandom: testu01ocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c -ltestu01

clean:
	rm -f $(BIN)

.PHONY: all clean
