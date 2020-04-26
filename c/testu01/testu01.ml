let barep rep =
  rep
  |> Array.map (fun x ->
      if (x lsr 32) <> 0 then invalid_arg "int32_of_int";
      Int32.of_int x)
  |> Bigarray.(Array1.of_array int32 c_layout)

external bbattery_SmallCrush : string -> (unit -> int) -> unit = "caml_bbattery_SmallCrush"
external bbattery_SmallCrushFile : string -> unit = "caml_bbattery_SmallCrushFile"
external bbattery_RepeatSmallCrush : string -> (unit -> int) -> 'a -> unit = "caml_bbattery_RepeatSmallCrush"
let bbattery_RepeatSmallCrush name bits rep = bbattery_RepeatSmallCrush name bits (barep rep)

external bbattery_Crush : string -> (unit -> int) -> unit = "caml_bbattery_Crush"
external bbattery_RepeatCrush : string -> (unit -> int) -> 'a -> unit = "caml_bbattery_RepeatCrush"
let bbattery_RepeatCrush name bits rep = bbattery_RepeatCrush name bits (barep rep)

external bbattery_BigCrush : string -> (unit -> int) -> unit = "caml_bbattery_BigCrush"
external bbattery_RepeatBigCrush : string -> (unit -> int) -> 'a -> unit = "caml_bbattery_RepeatBigCrush"
let bbattery_RepeatBigCrush name bits rep = bbattery_RepeatBigCrush name bits (barep rep)

external bbattery_Rabbit : string -> (unit -> int) -> float -> unit = "caml_bbattery_Rabbit"
external bbattery_RabbitFile : string -> unit = "caml_bbattery_RabbitFile"
external bbattery_RepeatRabbit : string -> (unit -> int) -> float -> 'a -> unit = "caml_bbattery_RepeatRabbit"
let bbattery_RepeatRabbit name bits nb rep = bbattery_RepeatRabbit name bits nb (barep rep)

external bbattery_Alphabit : string -> (unit -> int) -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external bbattery_AlphabitFile : string -> float -> unit = "caml_bbattery_AlphabitFile"
external bbattery_RepeatAlphabit : string -> (unit -> int) -> float -> int -> int -> 'a -> unit = "camlbytecode_bbattery_RepeatAlphabit" "caml_bbattery_RepeatAlphabit"
let bbattery_RepeatAlphabit name bits nb r s rep = bbattery_RepeatAlphabit name bits nb r s (barep rep)

external bbattery_BlockAlphabit : string -> (unit -> int) -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external bbattery_BlockAlphabitFile : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"
external bbattery_RepeatBlockAlphabit : string -> (unit -> int) -> float -> int -> int -> 'a -> int -> unit = "camlbytecode_bbattery_RepeatBlockAlphabit" "caml_bbattery_RepeatBlockAlphabit"
let bbattery_RepeatBlockAlphabit name bits nb r s rep w = bbattery_RepeatBlockAlphabit name bits nb r s (barep rep) w

external bbattery_pseudoDIEHARD : string -> (unit -> int) -> unit = "caml_bbattery_pseudoDIEHARD"
