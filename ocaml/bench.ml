open Xoshiro
module B = Core_bench.Bench
module Command = Core.Command

let main () =
  Random.self_init ();
  Command.run (B.make_command [
    B.Test.create ~name:"Random.bits" (fun () ->
      ignore (Random.bits ()));
    B.Test.create ~name:"X256pp.Int.bits" (fun () ->
      ignore (X256pp.Int.bits ()));
    B.Test.create ~name:"X256pp.Int64.bits" (fun () ->
      ignore (X256pp.Int64.bits ()));
  ])

let () = main ()
