open Xoshiro
module B = Core_bench.Bench
module Command = Core.Command

let bits () =
  Command.run (B.make_command [
    B.Test.create ~name:"Random.bits" (fun () ->
      ignore (Random.bits ()));

    B.Test.create ~name:"X256pp.Int.bits" (fun () ->
      ignore (X256pp.Int.bits ()));

    B.Test.create ~name:"X256pp.Int64.bits" (fun () ->
      ignore (X256pp.Int64.bits ()));
    B.Test.create ~name:"X256pp.Int64.bits62" (fun () ->
      ignore (X256pp.Int64.bits62 ()));

    B.Test.create ~name:"X256pp.C.bits" (fun () ->
      ignore (X256pp.C.bits ()));
    B.Test.create ~name:"X256pp.C.bits62" (fun () ->
      ignore (X256pp.C.bits62 ()));
  ])

let float () =
  Random.self_init ();
  Command.run (B.make_command [
    B.Test.create ~name:"Random.float" (fun () ->
      ignore (Random.float 1.));
    B.Test.create ~name:"X256.Int.float1" (fun () ->
      ignore (X256pp.Int.float1 1.));
    B.Test.create ~name:"X256.Int.float2" (fun () ->
      ignore (X256pp.Int.float2 1.));
    B.Test.create ~name:"X256pp.Int64.float" (fun () ->
      ignore (X256pp.Int64.float 1.));
    B.Test.create ~name:"X256pp.C.float" (fun () ->
      ignore (X256pp.C.float 1.));
  ])

let rawfloat () =
  Command.run (B.make_command [
    B.Test.create ~name:"X256.Int.rawfloat1" (fun () ->
      ignore (X256pp.Int.rawfloat1 ()));
    B.Test.create ~name:"X256.Int.rawfloat2" (fun () ->
      ignore (X256pp.Int.rawfloat2 ()));
  ])

let () =
  rawfloat ();
  bits ();
  float ()
