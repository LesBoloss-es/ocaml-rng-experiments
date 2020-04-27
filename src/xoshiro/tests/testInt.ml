open Xoshiro

let int_int_to_int64 (hi, lo) =
  let open Int64 in
  logxor (shift_left (of_int hi) 32) (of_int lo)

let int64_to_int_int n =
  let open Int64 in
  let hi = to_int (shift_right_logical n 32) in
  let lo = to_int (logand n 0xFFFFFFFFL) in
  (hi, lo)

let test_compare nb f g =
  for _ = 1 to nb do
    assert (f () = g ())
  done

let ocaml_seed seed =
  let s = ref seed in
  for i = 0 to 3 do
    let hi, lo = Splitmix.Sm64.next s |> int64_to_int_int in
    X256pp.Int.state.(2 * i) <- hi;
    X256pp.Int.state.(2 * i + 1) <- lo
  done

let () =
  (* Chosen by fair dice rool. Guaranted to be random. *)
  (* https://xkcd.com/221/ *)
  let seed = 0xc6bb1e08d1a33f2fL in
  Reference.seed seed;
  ocaml_seed seed;
  test_compare
    1_000_000
    Reference.next
    (fun () ->
      X256pp.Int.next () |> int_int_to_int64)
