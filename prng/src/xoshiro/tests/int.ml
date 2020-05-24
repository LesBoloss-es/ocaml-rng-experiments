open Xoshiro

let int_int_to_int64 (hi, lo) =
  let open Stdlib.Int64 in
  logxor (shift_left (of_int hi) 32) (of_int lo)

let int64_to_int_int n =
  let open Stdlib.Int64 in
  let hi = to_int (shift_right_logical n 32) in
  let lo = to_int (logand n 0xFFFFFFFFL) in
  (hi, lo)

let ocaml_seed seed =
  let s = ref seed in
  for i = 0 to 3 do
    let hi, lo = Splitmix.Sm64.next s |> int64_to_int_int in
    X256pp.Int.state.(2 * i) <- hi;
    X256pp.Int.state.(2 * i + 1) <- lo
  done

let () =
  Testutils.run
    ~seed_f:ocaml_seed
    ~next:(fun () -> X256pp.Int.next () |> int_int_to_int64)
