open Splitmix

let () =
  let n =
    if Array.length Sys.argv = 2
    then int_of_string Sys.argv.(1)
    else 10
  in

  let state = ref 0xdead42beef37ca7aL in
  for _ = 1 to n do
    Format.printf "%016Lx@." (Sm64.next state)
  done
