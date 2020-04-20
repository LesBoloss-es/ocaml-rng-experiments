(** Different implementations of xoshiro256++ *)

let u32mask = (1 lsl 32) - 1

(** The four 64-bits unsigned integers of xoshiro256++ are represented by eight
   ocaml 63-bits signed integers. *)
module Int = struct
  let state = [|
    0xdeadbeef;
    0xdeadbeef;
    0x42424242;
    0x42424242;
    0x37373737;
    0x37373737;
    0xca7aca7a;
    0xca7aca7a
  |]

  (** xoshiro's next function: return 64 random bits as two 32bits ocaml
    integers. *)
  let next () =
    (* const uint64_t result = rotl(s[0] + s[3], 23) + s[0]; *)
    let s03lo = state.(1) + state.(7) in
    let s03hi = (state.(0) + state.(6) + (s03lo lsr 32)) land u32mask in
    let s03lo = s03lo land u32mask in
    let rotlo = ((s03lo lsl 23) land u32mask) lor (s03hi lsr 9) in
    let rothi = ((s03hi lsl 23) land u32mask) lor (s03lo lsr 9) in
    let reslo = rotlo + state.(1) in
    let reshi = (rothi + state.(0) + (reslo lsr 32)) land u32mask in
    let reslo = reslo land u32mask in

    (* const uint64_t t = s[1] << 17; *)
    let tlo = (state.(3) lsl 17) land u32mask in
    let thi = ((state.(2) lsl 17) land u32mask) lor (state.(3) lsr 15) in

    (* s[2] ^= s[0]; *)
    state.(4) <- state.(4) lxor state.(0);
    state.(5) <- state.(5) lxor state.(1);

    (* s[3] ^= s[1]; *)
    state.(6) <- state.(6) lxor state.(2);
    state.(7) <- state.(7) lxor state.(3);

    (* s[1] ^= s[2]; *)
    state.(2) <- state.(2) lxor state.(4);
    state.(3) <- state.(3) lxor state.(5);

    (* s[0] ^= s[3]; *)
    state.(0) <- state.(0) lxor state.(6);
    state.(1) <- state.(1) lxor state.(7);

    (* s[2] ^= t; *)
    state.(4) <- state.(4) lxor thi;
    state.(5) <- state.(5) lxor tlo;

    (* s[3] = rotl(s[3], 45); *)
    let s3lo = state.(7) in
    let s3hi = state.(6) in
    state.(7) <- ((s3hi lsl 13)) land u32mask lor (s3lo lsr 19);
    state.(6) <- (s3hi lsr 19) lor ((s3lo lsl 13) land u32mask);

    (* return result; *)
    reshi, reslo

  (** Same interface as OCaml's Random.bits function. Wastes 2 random bits out
    of 62 at each call. *)
  let bits =
    let b = ref false in
    let r = ref 0 in
    fun () ->
      if !b then !r
      else
        let h, l = next () in
        let () = r := l land u32mask in
        let () = b := true in
        h land u32mask
end

(** Using OCaml's Int64 module *)
module Int64 = struct
  (* XXX. This is a bad default state, do proper initialisation. *)
  let s = [|
    0xdeadbeefdeadbeefL;
    0x4242424242424242L;
    0x3737373737373737L;
    0xca7aca7aca7aca7aL
  |]

  let[@inline] rotl x k =
    let open Int64 in
    logor (shift_left x k) (shift_right_logical x (64 - k))

  let ( .!() ) = Array.unsafe_get
  let ( .!()<- ) = Array.unsafe_set

  let next () =
    let open Int64 in

    (* const uint64_t result = rotl(s[0] + s[3], 23) + s[0]; *)
    let result = Int64.add (rotl (Int64.add s.!(0) s.!(3)) 23) s.!(0) in

    (* const uint64_t t = s[1] << 17; *)
    let t = shift_left s.!(1) 17 in

    (* s[2] ^= s[0]; *)
    s.!(2) <- logxor s.!(2) s.!(0);
    (* s[3] ^= s[1]; *)
    s.!(3) <- logxor s.!(3) s.!(1);
    (* s[1] ^= s[2]; *)
    s.!(1) <- logxor s.!(1) s.!(2);
    (* s[0] ^= s[3]; *)
    s.!(0) <- logxor s.!(0) s.!(3);

    (* s[2] ^= t; *)
    s.!(2) <- logxor s.!(2) t;

    (* s[3] = rotl(s[3], 45); *)
    s.!(3) <- rotl s.!(3) 45;

    (* return result; *)
    result

  (* Interface similar to Stdlib.Random *)

  let bits =
    let b = ref false in
    let r = ref 0 in
    fun () ->
      if !b then !r
      else
        let n = next () in
        let () = r := Int64.to_int n land u32mask in
        let () = b := true in
        Int64.(to_int (shift_right_logical n 34))

  let bits62 () =
    let n = next () in
    Int64.(to_int (shift_right_logical n 2))

  let int =
    let rec aux n =
      let r = bits () in
      let v = r mod n in
      if r - v > 0x3FFFFFFF - n + 1 then aux n else v
    in
    fun n ->
      if n > 0x3FFFFFFF || n <= 0
      then invalid_arg "x256pp.int"
      else aux n

  let int62 () =
    let rec aux n =
      let r = bits62 () in
      let v = r mod n in
      if r - v > 0x3FFFFFFF_FFFFFFFF - n + 1 then aux n else v
    in
    fun n ->
      if n <= 0
      then invalid_arg "x256pp.int62"
      else aux n

  let float x =
    Int64.(to_float (shift_right_logical (next ()) 11)) *. 0x1.0p-53
end

module C = struct
  external bits: unit -> int = "x256pp_bits"
  external bits62: unit -> int = "x256pp_bits62"
  external float: float -> float = "x256pp_double"
end
