Adding a binding
----------------

- Each C file should give birth to two corresponding bindings files: a ML file
  and a C stubs file. For instance, `usoft.c` from TestU01 will be binded in
  `usoft.ml` and `usoft_stubs.c`.

- Each destructor should have its appropriate “custom operations block” where it
  is used in the finalizer. The finalizer should usually simply unbox the type
  and call the desctructor on the unboxed version.

- Each constructor should box `unif01_Gen` using the appropriate “custom
  operations block”. This tells the GC which finalizer to call when it wants to
  get rid of the block.
