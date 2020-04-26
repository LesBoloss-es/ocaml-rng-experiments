module MadeRandom = MakeRandom.Basic(Random)

let seed = 657115043853

type output =
  { bits : int ;
    int : int ;
    int32 : int32 ;
    nativeint : nativeint ;
    int64 : int64 ;
    float : float ;
    bool : bool }

let run (module R : MakeRandom.BASIC) =
  let bits = R.bits () in
  let int = R.int (1 lsl 30 - 1) in
  let int32 = R.int32 Int32.max_int in
  let nativeint = R.nativeint Nativeint.max_int in
  let int64 = R.int64 Int64.max_int in
  let float = R.float 1. in
  let bool = R.bool () in
  { bits ; int ; int32 ; nativeint ; int64 ; float ; bool }

let run_n (module R : MakeRandom.BASIC) n =
  let rec run_n acc n =
    if n <= 0 then acc
    else run_n (run (module R) :: acc) (n-1)
  in
  run_n [] n

let n =
  if Array.length Sys.argv > 1
  then int_of_string Sys.argv.(1)
  else 10

let random =
  Random.init seed;
  run_n (module Random) n

let maderandom =
  Random.init seed;
  run_n (module MadeRandom) n

let () = assert (random = maderandom)
