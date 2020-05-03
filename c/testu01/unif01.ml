type gen

external create_extern_gen_bits : string -> (unit -> int) -> gen = "caml_unif01_CreateExternGenBits"

external delete_extern_gen_bits : gen -> unit = "caml_unif01_DeleteExternGenBits"
