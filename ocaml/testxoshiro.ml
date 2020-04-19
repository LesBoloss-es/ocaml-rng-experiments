open Xoshiro

let () =
  let n =
    if Array.length Sys.argv = 2
    then int_of_string Sys.argv.(1)
    else 10
  in

  for _ = 1 to n do
    let hi, lo = X256pp.Int.next () in
    Format.printf "%08x%08x " hi lo;
    Format.printf "%016Lx@." (X256pp.Int64.next ());
  done
