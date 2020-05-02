let barep rep =
  rep
  |> Array.map (fun x ->
      if (x lsr 32) <> 0 then invalid_arg "int32_of_int";
      Int32.of_int x)
  |> Bigarray.(Array1.of_array int32 c_layout)

type unif01_Gen

external unif01_CreateExternGenBits : string -> (unit -> int) -> unif01_Gen = "caml_unif01_CreateExternGenBits"
external unif01_DeleteExternGenBits : unif01_Gen -> unit = "caml_unif01_DeleteExternGenBits"

external bbattery_SmallCrush : unif01_Gen -> unit = "caml_bbattery_SmallCrush"
external bbattery_SmallCrushFile : string -> unit = "caml_bbattery_SmallCrushFile"
external bbattery_RepeatSmallCrush : unif01_Gen -> 'a -> unit = "caml_bbattery_RepeatSmallCrush"
let bbattery_RepeatSmallCrush gen rep = bbattery_RepeatSmallCrush gen (barep rep)

external bbattery_Crush : unif01_Gen -> unit = "caml_bbattery_Crush"
external bbattery_RepeatCrush : unif01_Gen -> 'a -> unit = "caml_bbattery_RepeatCrush"
let bbattery_RepeatCrush gen rep = bbattery_RepeatCrush gen (barep rep)

external bbattery_BigCrush : unif01_Gen -> unit = "caml_bbattery_BigCrush"
external bbattery_RepeatBigCrush : unif01_Gen -> 'a -> unit = "caml_bbattery_RepeatBigCrush"
let bbattery_RepeatBigCrush gen rep = bbattery_RepeatBigCrush gen (barep rep)

external bbattery_Rabbit : unif01_Gen -> float -> unit = "caml_bbattery_Rabbit"
external bbattery_RabbitFile : string -> unit = "caml_bbattery_RabbitFile"
external bbattery_RepeatRabbit : unif01_Gen -> float -> 'a -> unit = "caml_bbattery_RepeatRabbit"
let bbattery_RepeatRabbit gen nb rep = bbattery_RepeatRabbit gen nb (barep rep)

external bbattery_Alphabit : unif01_Gen -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external bbattery_AlphabitFile : string -> float -> unit = "caml_bbattery_AlphabitFile"
external bbattery_RepeatAlphabit : unif01_Gen -> float -> int -> int -> 'a -> unit = "caml_bbattery_RepeatAlphabit"
let bbattery_RepeatAlphabit gen nb r s rep = bbattery_RepeatAlphabit gen nb r s (barep rep)

external bbattery_BlockAlphabit : unif01_Gen -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external bbattery_BlockAlphabitFile : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"
external bbattery_RepeatBlockAlphabit : unif01_Gen -> float -> int -> int -> 'a -> int -> unit = "camlbytecode_bbattery_RepeatBlockAlphabit" "caml_bbattery_RepeatBlockAlphabit"
let bbattery_RepeatBlockAlphabit gen nb r s rep w = bbattery_RepeatBlockAlphabit gen nb r s (barep rep) w

external bbattery_pseudoDIEHARD : unif01_Gen -> unit = "caml_bbattery_pseudoDIEHARD"

external bbattery_FIPS_140_2 : unif01_Gen -> unit = "caml_bbattery_FIPS_140_2"
external bbattery_FIPS_140_2File : string -> unit = "caml_bbattery_FIPS_140_2File"
