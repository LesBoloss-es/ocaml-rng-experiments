let barep rep =
  rep
  |> Array.map (fun x ->
      if (x lsr 32) <> 0 then invalid_arg "int32_of_int";
      Int32.of_int x)
  |> Bigarray.(Array1.of_array int32 c_layout)

external smallCrush : Unif01.gen -> unit = "caml_bbattery_SmallCrush"
external smallCrushFile : string -> unit = "caml_bbattery_SmallCrushFile"
external repeatSmallCrush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatSmallCrush"
let repeatSmallCrush gen rep = repeatSmallCrush gen (barep rep)

external cush : Unif01.gen -> unit = "caml_bbattery_Crush"
external repeatCrush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatCrush"
let repeatCrush gen rep = repeatCrush gen (barep rep)

external bigCrush : Unif01.gen -> unit = "caml_bbattery_BigCrush"
external repeatBigCrush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatBigCrush"
let repeatBigCrush gen rep = repeatBigCrush gen (barep rep)

external rabbit : Unif01.gen -> float -> unit = "caml_bbattery_Rabbit"
external rabbitFile : string -> unit = "caml_bbattery_RabbitFile"
external repeatRabbit : Unif01.gen -> float -> 'a -> unit = "caml_bbattery_RepeatRabbit"
let repeatRabbit gen nb rep = repeatRabbit gen nb (barep rep)

external alphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external alphabitFile : string -> float -> unit = "caml_bbattery_AlphabitFile"
external repeatAlphabit : Unif01.gen -> float -> int -> int -> 'a -> unit = "caml_bbattery_RepeatAlphabit"
let repeatAlphabit gen nb r s rep = repeatAlphabit gen nb r s (barep rep)

external blockAlphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external blockAlphabitFile : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"
external repeatBlockAlphabit : Unif01.gen -> float -> int -> int -> 'a -> int -> unit = "camlbytecode_bbattery_RepeatBlockAlphabit" "caml_bbattery_RepeatBlockAlphabit"
let repeatBlockAlphabit gen nb r s rep w = repeatBlockAlphabit gen nb r s (barep rep) w

external pseudoDIEHARD : Unif01.gen -> unit = "caml_bbattery_pseudoDIEHARD"

external fIPS_140_2 : Unif01.gen -> unit = "caml_bbattery_FIPS_140_2"
external fIPS_140_2File : string -> unit = "caml_bbattery_FIPS_140_2File"
