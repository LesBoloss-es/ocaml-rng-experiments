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

module Random_Stdlib       = RandomFunctor.Basic(Random)
module Random_X256pp_Int   = RandomFunctor.Basic(X256pp.Int)
module Random_X256pp_Int64 = RandomFunctor.Basic(X256pp.Int64)
module Random_X256pp_C     = RandomFunctor.Basic(X256pp.C)

let float () =
  Command.run @@ B.make_command [
    B.Test.create ~name:"Random.float" (fun () ->
        ignore (Random.float 1.));
    B.Test.create ~name:"X256pp.Int64.float" (fun () ->
        ignore (X256pp.Int64.float 1.));
    B.Test.create ~name:"X256pp.C.float" (fun () ->
        ignore (X256pp.C.float 1.));
    B.Test.create ~name:"RandomFunctor(Random).float" (fun () ->
        ignore (Random_Stdlib.float 1.));
    B.Test.create ~name:"RandomFunctor(X256pp.Int).float" (fun () ->
        ignore (Random_X256pp_Int.float 1.));
    B.Test.create ~name:"RandomFunctor(X256pp.Int64).float" (fun () ->
        ignore (Random_X256pp_Int64.float 1.));
    B.Test.create ~name:"RandomFunctor(X256pp.C).float" (fun () ->
        ignore (Random_X256pp_C.float 1.));
  ]

let int64 () =
  Command.run @@ B.make_command [
    B.Test.create ~name:"Random.int64" (fun () ->
        ignore (Random.int64 Int64.max_int));
    B.Test.create ~name:"RandomFunctor(Random).int64" (fun () ->
        ignore (Random_Stdlib.int64 Int64.max_int));
    B.Test.create ~name:"RandomFunctor(X256pp.Int).int64" (fun () ->
        ignore (Random_X256pp_Int.int64 Int64.max_int));
    B.Test.create ~name:"RandomFunctor(X256pp.Int64).int64" (fun () ->
        ignore (Random_X256pp_Int64.int64 Int64.max_int));
    B.Test.create ~name:"RandomFunctor(X256pp.C).int64" (fun () ->
        ignore (Random_X256pp_C.int64 Int64.max_int));
  ]


let () =
  bits ();
  float ();
  int64 ()
