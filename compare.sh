#!/bin/sh

set -e

compare () {
  echo "Comparing '$1' and '$2'..."
  tmp="$(mktemp)"
  "$1" 1000 > "$tmp"
  test -z "$("$2" 1000 | diff "$tmp" -)"
  rm -f "$tmp"
}

make -C ocaml tests
make -C c all

compare ocaml/_build/default/tests/splitmix.exe c/testsplitmix
echo OK!
