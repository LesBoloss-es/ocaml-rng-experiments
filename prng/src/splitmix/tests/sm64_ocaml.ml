open Splitmix

let test_compare nb f g =
  for _ = 1 to nb do
    assert (f () = g ())
  done

let () =
  (* Chosen by fair dice rool. Guaranted to be random. *)
  (* https://xkcd.com/221/ *)
  let seed = 0xdd6d0e2e849e51adL in
  let ocaml_state = ref seed in

  Reference.seed seed;
  test_compare
    1_000_000
    Reference.next
    (fun () -> Sm64.next ocaml_state)
