TestU01
=======

This directory includes TestU01 1.2.3 as provided by
http://simul.iro.umontreal.ca/testu01/tu01.html

The compilation seems to work rather well. However, the project has not been
made up to date with the newer version of autoconf, causing problems if one
attempts to compile the whole thing. A mitigation is to make sure that the
access and modification times from the zip file are unchanged. This is why, in
particular, we provide the zip file directly. Otherwise, Dune's sandboxing would
loose this information and compilation would fail.
