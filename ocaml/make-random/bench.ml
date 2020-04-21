module B = Core_bench.Bench
module Command = Core.Command

module MadeRandom = MakeRandom.Basic(Random)

let seed = 657115043853

let bits () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.bits" (fun `init ->
        Random.init seed;
        fun () -> Random.bits ());
    B.Test.create_with_initialization ~name:"MakeRandom(Random).bits" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.bits ());
  ]

let int () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.int" (fun `init ->
        Random.init seed;
        fun () -> Random.int (1 lsl 30 - 1));
    B.Test.create_with_initialization ~name:"MakeRandom(Random).int" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.int (1 lsl 30 - 1));
  ]

let int32 () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.int32" (fun `init ->
        Random.init seed;
        fun () -> Random.int32 Int32.max_int);
    B.Test.create_with_initialization ~name:"MakeRandom(Random).int32" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.int32 Int32.max_int);
  ]

let nativeint () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.nativeint" (fun `init ->
        Random.init seed;
        fun () -> Random.nativeint Nativeint.max_int);
    B.Test.create_with_initialization ~name:"MakeRandom(Random).nativeint" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.nativeint Nativeint.max_int);
  ]

let int64 () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.int64" (fun `init ->
        Random.init seed;
        fun () -> Random.int64 Int64.max_int);
    B.Test.create_with_initialization ~name:"MakeRandom(Random).int64" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.int64 Int64.max_int);
  ]

let float () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.float" (fun `init ->
        Random.init seed;
        fun () -> Random.float 1.);
    B.Test.create_with_initialization ~name:"MakeRandom(Random).float" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.float 1.);
  ]

let bool () =
  Command.run @@ B.make_command [
    B.Test.create_with_initialization ~name:"Random.bool" (fun `init ->
        Random.init seed;
        fun () -> Random.bool ());
    B.Test.create_with_initialization ~name:"MakeRandom(Random).bool" (fun `init ->
        Random.init seed;
        fun () -> MadeRandom.bool ());
  ]

let () =
  bits ();
  int ();
  int32 ();
  nativeint ();
  int64 ();
  float ();
  bool ()
