let rotl x k =
  let open Int64 in
  logor (shift_left x k) (shift_right_logical x (64 - k))

let ( ^= ) s x = s := Int64.logxor !s x

let next (s: Int64.t ref) =
  let open Int64 in
  s := add !s 0x9e3779b97f4a7c15L;
  let z = !s in
  let z = mul (logxor z (shift_right_logical z 30)) 0xbf58476d1ce4e5b9L in
  let z = mul (logxor z (shift_right_logical z 27)) 0x94d049bb133111ebL in
  logxor (shift_right_logical z 31) z


include MakeRandom.Full(struct
  type state = Int64.t ref

  let default = ref 0x25dc4fcdfae36682L

  let new_state () = ref 0L

  let assign s1 s2 = s1 := !s2

  let full_init s seeds =
    Array.iteri
      (fun i n ->
        (* rotate the bits to make a better use of the 8bits numbers given by
           caml_sys_random_seed. *)
        s ^= rotl (Int64.of_int n) (8 * (i mod 8)))
      (if seeds = [||] then [|0x25dc4fcd|] else seeds)

  let bits =
    let buf = ref 0 in
    let buf_full = ref false in
    fun state ->
      if !buf_full then begin
        buf_full := false;
        !buf
      end else begin
        let n = next state in
        buf := Int64.(to_int (shift_right_logical n 34));
        (Int64.to_int n) land 0x3FFFFFFF
      end
end)
