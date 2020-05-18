let run ~seed_f ~next =
  let seed = ref 0xdd6d0e2e849e51adL in
  let nb_iterations = ref (-1) in

  let speclist = [
    (
      "--nb",
      Arg.Set_int nb_iterations,
      " Number of random integers to generate"
    );
    (
      "--seed",
      Arg.String (fun n -> seed := Int64.of_string n),
      " 64-bit seed");
  ] in

  let usage =
    Format.sprintf "%s [--seed=SEED] [--nb=N]" Sys.argv.(0)
  in

  Arg.parse speclist (fun _ -> invalid_arg "run") usage;
  seed_f !seed;
  let i = ref 0 in
  while !i <> !nb_iterations do
    Format.printf "%Lx@." (next ());
    incr i
  done
