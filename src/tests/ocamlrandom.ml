let () =
  let n =
    if Array.length Sys.argv = 2
    then int_of_string Sys.argv.(1)
    else 10
  in

  for _ = 1 to n do
    Format.printf "%08x\n" (Random.bits ())
  done
