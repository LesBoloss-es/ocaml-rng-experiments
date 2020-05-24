open Splitmix

let () =
  let state = ref 0L in
  Testutils.run
    ~seed_f:(fun s -> state := s)
    ~next:(fun () -> Sm64.next state)
