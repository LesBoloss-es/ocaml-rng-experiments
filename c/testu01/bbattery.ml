let barep rep =
  rep
  |> Array.map (fun x ->
      if (x lsr 32) <> 0 then invalid_arg "int32_of_int";
      Int32.of_int x)
  |> Bigarray.(Array1.of_array int32 c_layout)

external small_crush : Unif01.gen -> unit = "caml_bbattery_SmallCrush"
external small_crush_file : string -> unit = "caml_bbattery_SmallCrushFile"
external repeat_small_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatSmallCrush"
let repeat_small_crush gen rep = repeat_small_crush gen (barep rep)

external crush : Unif01.gen -> unit = "caml_bbattery_Crush"
external repeat_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatCrush"
let repeat_crush gen rep = repeat_crush gen (barep rep)

external big_crush : Unif01.gen -> unit = "caml_bbattery_BigCrush"
external repeat_big_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatBigCrush"
let repeat_big_crush gen rep = repeat_big_crush gen (barep rep)

external rabbit : Unif01.gen -> float -> unit = "caml_bbattery_Rabbit"
external rabbit_file : string -> unit = "caml_bbattery_RabbitFile"
external repeat_rabbit : Unif01.gen -> float -> 'a -> unit = "caml_bbattery_RepeatRabbit"
let repeat_rabbit gen nb rep = repeat_rabbit gen nb (barep rep)

external alphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external alphabit_file : string -> float -> unit = "caml_bbattery_AlphabitFile"
external repeat_alphabit : Unif01.gen -> float -> int -> int -> 'a -> unit = "caml_bbattery_RepeatAlphabit"
let repeat_alphabit gen nb r s rep = repeat_alphabit gen nb r s (barep rep)

external block_alphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external block_alphabit_file : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"
external repeat_block_alphabit : Unif01.gen -> float -> int -> int -> 'a -> int -> unit = "camlbytecode_bbattery_RepeatBlockAlphabit" "caml_bbattery_RepeatBlockAlphabit"
let repeat_block_alphabit gen nb r s rep w = repeat_block_alphabit gen nb r s (barep rep) w

external pseudo_diehard : Unif01.gen -> unit = "caml_bbattery_pseudoDIEHARD"

external fips_140_2 : Unif01.gen -> unit = "caml_bbattery_FIPS_140_2"
external fips_140_2_file : string -> unit = "caml_bbattery_FIPS_140_2File"
