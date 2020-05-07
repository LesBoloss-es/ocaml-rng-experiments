TestU01 Assets
==============

For convenience, this directory includes assets from TestU01, obtained from
http://simul.iro.umontreal.ca/testu01/tu01.html. Namely:

- The source files; a zip file containing all the sources of the C library, as
  well as the TeX documentation.

- An example Dune file that compiles it as a "foreign build". We are not using
  it in the project as we expect the library to be present on the system when
  installing the OCaml bindings.

- The (short) user's guide, as of May 16th, 2013.

- The paper:

  > Pierre L’Ecuyer and Richard Simard. 2007. TestU01: A C library for empirical
  > testing of random number generators. ACM Trans. Math. Softw. 33, 4, Article
  > 22 (August 2007), 40 pages. DOI:https://doi.org/10.1145/1268776.1268777

Manual Installation
-------------------

Manual installation of TestU01 can be done from these assets by:

- Unzipping the sources and changing directory to the newly created one.

- Running `./configure`. The `--prefix` option allows to specify where the
  library will need to be installed.

- Running `make` and `make install`.

Do not forget that, if you installed TestU01 in a non-standard place, you will
need to set `C_INCLUDE_PATH` (for header files) and `LIBRARY_PATH` (for the
library) accordingly.
