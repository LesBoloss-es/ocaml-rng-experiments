let barep size rep =
  if Array.length rep <> size + 1 then
    invalid_arg "wrong size for repeat array";
  rep
  |> Array.map (fun x ->
      if (x lsr 32) <> 0 then
        invalid_arg "value too high in repeat array";
      Int32.of_int x)
  |> Bigarray.(Array1.of_array int32 c_layout)

external small_crush : Unif01.gen -> unit = "caml_bbattery_SmallCrush"
external small_crush_file : string -> unit = "caml_bbattery_SmallCrushFile"
external repeat_small_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatSmallCrush"
let ntests_small_crush = 10
let repeat_small_crush gen rep = repeat_small_crush gen (barep ntests_small_crush rep)

external crush : Unif01.gen -> unit = "caml_bbattery_Crush"
external repeat_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatCrush"
let ntests_crush = 96
let repeat_crush gen rep = repeat_crush gen (barep ntests_crush rep)

external big_crush : Unif01.gen -> unit = "caml_bbattery_BigCrush"
external repeat_big_crush : Unif01.gen -> 'a -> unit = "caml_bbattery_RepeatBigCrush"
let ntests_bigcrush = 106
let repeat_big_crush gen rep = repeat_big_crush gen (barep ntests_bigcrush rep)

external rabbit : Unif01.gen -> float -> unit = "caml_bbattery_Rabbit"
external rabbit_file : string -> unit = "caml_bbattery_RabbitFile"
external repeat_rabbit : Unif01.gen -> float -> 'a -> unit = "caml_bbattery_RepeatRabbit"
let ntests_rabbit = 26
let repeat_rabbit gen nb rep = repeat_rabbit gen nb (barep ntests_rabbit rep)

external alphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external alphabit_file : string -> float -> unit = "caml_bbattery_AlphabitFile"
external repeat_alphabit : Unif01.gen -> float -> int -> int -> 'a -> unit = "caml_bbattery_RepeatAlphabit"
let ntests_alphabit = 9
let repeat_alphabit gen nb r s rep = repeat_alphabit gen nb r s (barep ntests_alphabit rep)

external block_alphabit : Unif01.gen -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external block_alphabit_file : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"
external repeat_block_alphabit : Unif01.gen -> float -> int -> int -> 'a -> int -> unit = "camlbytecode_bbattery_RepeatBlockAlphabit" "caml_bbattery_RepeatBlockAlphabit"
let ntests_block_alphabit = ntests_alphabit
let repeat_block_alphabit gen nb r s rep w = repeat_block_alphabit gen nb r s (barep ntests_block_alphabit rep) w

external pseudo_diehard : Unif01.gen -> unit = "caml_bbattery_pseudoDIEHARD"
let ntests_diehard = 15

external fips_140_2 : Unif01.gen -> unit = "caml_bbattery_FIPS_140_2"
external fips_140_2_file : string -> unit = "caml_bbattery_FIPS_140_2File"
let ntests_fips_140_2 = 4
