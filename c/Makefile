BIN =\
		 testxoshiro\
		 testsplitmix\
		 testocamlrandom\
		 testu01ocamlrandom

all: $(BIN)

testsplitmix: testsplitmix.c splitmix64.c splitmix64.h
	cc -o $@ $< splitmix64.c

testxoshiro: testxoshiro.c xoshiro256pp.c xoshiro256pp.h
	cc -o $@ $< xoshiro256pp.c

testocamlrandom: testocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c -ltestu01

testu01ocamlrandom: testu01ocamlrandom.c ocamlrandom.c ocamlrandom.h
	cc -o $@ $< ocamlrandom.c -ltestu01

clean:
	rm -f $(BIN)

.PHONY: all clean
