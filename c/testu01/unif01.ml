type gen

external createExternGenBits : string -> (unit -> int) -> gen = "caml_unif01_CreateExternGenBits"

external deleteExternGenBits : gen -> unit = "caml_unif01_DeleteExternGenBits"
