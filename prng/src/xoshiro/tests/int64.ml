open Xoshiro

let test_compare nb f g =
  for _ = 1 to nb do
    assert (f () = g ())
  done

let ocaml_seed seed =
  let s = ref seed in
  for i = 0 to 3 do
    X256pp.Int64.s.(i) <- Splitmix.Sm64.next s
  done

let () =
  (* Chosen by fair dice rool. Guaranted to be random. *)
  (* https://xkcd.com/221/ *)
  let seed = 0xc6bb1e08d1a33f2fL in
  Reference.seed seed;
  ocaml_seed seed;
  test_compare 1_000_000 Reference.next X256pp.Int64.next
