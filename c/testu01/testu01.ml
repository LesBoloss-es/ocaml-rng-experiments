external bbattery_SmallCrush : string -> (unit -> int) -> unit = "caml_bbattery_SmallCrush"
external bbattery_SmallCrushFile : string -> unit = "caml_bbattery_SmallCrushFile"

external bbattery_Crush : string -> (unit -> int) -> unit = "caml_bbattery_Crush"

external bbattery_BigCrush : string -> (unit -> int) -> unit = "caml_bbattery_BigCrush"

external bbattery_Rabbit : string -> (unit -> int) -> float -> unit = "caml_bbattery_Rabbit"
external bbattery_RabbitFile : string -> unit = "caml_bbattery_RabbitFile"

external bbattery_Alphabit : string -> (unit -> int) -> float -> int -> int -> unit = "caml_bbattery_Alphabit"
external bbattery_AlphabitFile : string -> float -> unit = "caml_bbattery_AlphabitFile"

external bbattery_BlockAlphabit : string -> (unit -> int) -> float -> int -> int -> unit = "caml_bbattery_BlockAlphabit"
external bbattery_BlockAlphabitFile : string -> float -> unit = "caml_bbattery_BlockAlphabitFile"

external bbattery_pseudoDIEHARD : string -> (unit -> int) -> unit = "caml_bbattery_pseudoDIEHARD"
