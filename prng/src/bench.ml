open Xoshiro
module B = Core_bench.Bench
module Command = Core.Command

module Random_Stdlib       = MakeRandom.Basic(Random)
module Random_X256pp_Int   = MakeRandom.Basic(X256pp.Int)
module Random_X256pp_Int64 = MakeRandom.Basic(X256pp.Int64)

let bits () =
  Command.run @@ B.make_command [
    B.Test.create ~name:"Random.bits" (fun () ->
        Random.bits ());
    B.Test.create ~name:"X256pp.Int.bits" (fun () ->
        X256pp.Int.bits ());
    B.Test.create ~name:"X256pp.Int64.bits" (fun () ->
        X256pp.Int64.bits ());
    B.Test.create ~name:"X256pp.Int64.bits62" (fun () ->
        X256pp.Int64.bits62 ());
  ]

let float () =
  Command.run @@ B.make_command [
    B.Test.create ~name:"Random.float" (fun () ->
        Random.float 1.);
    B.Test.create ~name:"X256pp.Int64.float" (fun () ->
        X256pp.Int64.float 1.);
    B.Test.create ~name:"MakeRandom(X256pp.Int).float" (fun () ->
        Random_X256pp_Int.float 1.);
    B.Test.create ~name:"MakeRandom(X256pp.Int64).float" (fun () ->
        Random_X256pp_Int64.float 1.);
  ]

let int64 () =
  Command.run @@ B.make_command [
    B.Test.create ~name:"MakeRandom(Random).int64" (fun () ->
        Random_Stdlib.int64 Int64.max_int);
    B.Test.create ~name:"MakeRandom(X256pp.Int).int64" (fun () ->
        Random_X256pp_Int.int64 Int64.max_int);
    B.Test.create ~name:"MakeRandom(X256pp.Int64).int64" (fun () ->
        Random_X256pp_Int64.int64 Int64.max_int);
  ]

let () =
  bits ();
  float ();
  int64 ()
