TestU01 Bindings for OCaml
==========================

From *TestU01 User’s guide, compact version*:

> It is also possible to test one’s own or an external generator (that is, a
> generator that is not predefined in TestU01) very easily [...] as long as this
> generator is programmed in C.

Wrong. Behold: TestU01 bindings for OCaml.

Installation
------------

These OCaml bindings require TestU01 to be installed on your computer. It is
possible your distribution provides a package for TestU01 already:

- for Debian buster and bullseye: `libtestu01`.

- for Archlinux: `testu01`, in AUR.

Naming Convention
-----------------

The naming convention remains close to that of TestU01, on purpose. The
differences are the following:

- The library is all under a main module `Testu01`.

- The functions, variables and types are not prefixed by the part of the library
  they belong to, but are in a corresponding module.

- The names are with underscore and not in Camel case.

- The global variables are read and modified using getters and setters.

For instance, the binding for the function:

    void bbattery_RepeatBigCrush(unif01_Gen* gen, int[] rep);

will be:

    val Testu01.Bbattery.repeat_big_crush : Unif01.gen -> int array -> unit

and the binding for the variable:

    extern double ftab_Suspectp;

will be:

    val Testu01.Ftab.get_suspectp : unit -> float
    val Testu01.Ftab.set_suspectp : float -> unit

Example Use
-----------

Let us say we want to asses the quality of the PRNG in OCaml's standard library.
We can simply write the following file:

    let () =
      let gen = Testu01.Unif01.create_extern_gen_bits "stdlib" Random.bits in
      Testu01.Bbattery.crush gen

that creates a TestU01 generator of type `Unif01.gen` out of a function `unit ->
bits` and applies the test battery "crush" to it (this PRNG passes all tests in
the "small crush" battery). It can then be compiled to an executable that takes
about an hour to run and writes a report on the standard output, similar to the
following:

           Test                          p-value
     ----------------------------------------------
     11  BirthdaySpacings, t = 2          eps
     31  Gap, r = 0                       eps
     33  Gap, r = 0                       eps
     51  WeightDistrib, r = 0             eps
     52  WeightDistrib, r = 8             eps
     53  WeightDistrib, r = 16            eps
     85  HammingIndep, L = 30             0.0006
     ----------------------------------------------

Some tests (with p-value `eps`) do not pass. For some tests, the p-value is
suspicious, but we cannot really conclude anything from it. Luckily, TestU01
provides `Repeat*` variants for its test batteries. They allow to provide, *via*
an array, the number of times each test must be run. Let us repeat the 85th
test, HammingIndep with L = 30, 10 times (and the others 0 times) to decide
whether the p-value is indeed low or if it was an unlucky artefact. For that, we
can write the following file:

    let () =
      let gen = Testu01.Unif01.create_extern_gen_bits "stdlib" Random.bits in
      let rep = Array.make 97 0 in
      rep.(85) <- 10;
      Testu01.Bbattery.repeat_crush gen rep

Running it takes about 5 minutes and writes the following report:

     All tests were passed

It was indeed an artefact, and `Random.bits` passes 85th test, HammingIndep with
L = 30.

For more information, we encourage you to refer to TestU01's user's guide.
