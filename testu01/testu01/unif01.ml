type gen

external create_extern_gen_bits : string -> (unit -> int) -> gen = "caml_unif01_CreateExternGenBits"

let create_extern_gen_bits name bits =
  (* Add a test that the [bits] function does not provide more than 30, in which
     case they would be lost. Doing the test every time does not have any real
     impact on the performances. *)
  create_extern_gen_bits name (fun () ->
      let b = bits () in
      if b lsr 30 <> 0 then
        invalid_arg "more than 30 bits received";
      b)
