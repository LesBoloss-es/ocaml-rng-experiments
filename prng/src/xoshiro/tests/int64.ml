open Xoshiro

let () =
  Testutils.run
    ~seed_f:(fun seed ->
      let s = ref seed in
      for i = 0 to 3 do
        X256pp.Int64.s.(i) <- Splitmix.Sm64.next s
      done)
    ~next:X256pp.Int64.next
