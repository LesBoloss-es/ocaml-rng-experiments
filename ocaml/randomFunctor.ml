(** {1 Functor for the Random Module}

   This module provide functors to reproduce the interface of the standard
   library's Random module with other pseudo-random number generators. *)

(** {2 Type of the basic functions} *)

module type BASIC = sig
  val bits : unit -> int
  val int : int -> int
  val int32 : Int32.t -> Int32.t
  val nativeint : Nativeint.t -> Nativeint.t
  val int64 : Int64.t -> Int64.t
  val float : float -> float
  val bool : unit -> bool
end

(** {2 Complete type of the module} *)

module type FULL = sig
  val init : int -> unit
  val full_init : int array -> unit
  val self_init : unit -> unit
  include BASIC
  module State : sig
    type t
    val make : int array -> t
    val make_self_init : unit -> t
    val copy : t -> t
    val bits : t -> int
    val int : t -> int -> int
    val int32 : t -> Int32.t -> Int32.t
    val nativeint : t -> Nativeint.t -> Nativeint.t
    val int64 : t -> Int64.t -> Int64.t
    val float : t -> float -> float
    val bool : t -> bool
  end
  val get_state : unit -> State.t
  val set_state : State.t -> unit
end

(** {2 Functor for the Full Interface} *)

module type FULLBITS = sig
  type state
  (** The type of PRNG states. *)

  val new_state : unit -> state
  (** Create a new non-initialised state. *)

  val assign : state -> state -> unit
  (** [assign s1 s2] copies [s2] into [s1]. *)

  val full_init : state -> int array -> unit
  (** Initialise a given state with a given seed. *)

  val bits : state -> int
  (** Provide 30 random bits in an integer. *)

  val default : state
  (** The default state to use for basic functions. *)
end

external random_seed: unit -> int array = "caml_sys_random_seed"

module Full (B : FULLBITS) : FULL = struct

  module State = struct
    type t = B.state

    let make seed =
      let result = B.new_state () in
      B.full_init result seed;
      result

    let make_self_init () = make (random_seed ())

    let copy s =
      let result = B.new_state () in
      B.assign result s;
      result

    let bits = B.bits

    (** The following is copied from Stdlib.Random.State.

       Copyright 1996 Institut National de Recherche en Informatique et en
       Automatique. *)

    let rec intaux s n =
      let r = bits s in
      let v = r mod n in
      if r - v > 0x3FFFFFFF - n + 1 then intaux s n else v

    let int s bound =
      if bound > 0x3FFFFFFF || bound <= 0
      then invalid_arg "Random.int"
      else intaux s bound

    let rec int32aux s n =
      let b1 = Int32.of_int (bits s) in
      let b2 = Int32.shift_left (Int32.of_int (bits s land 1)) 30 in
      let r = Int32.logor b1 b2 in
      let v = Int32.rem r n in
      if Int32.sub r v > Int32.add (Int32.sub Int32.max_int n) 1l
      then int32aux s n
      else v

    let int32 s bound =
      if bound <= 0l
      then invalid_arg "Random.int32"
      else int32aux s bound

    let rec int64aux s n =
      let b1 = Int64.of_int (bits s) in
      let b2 = Int64.shift_left (Int64.of_int (bits s)) 30 in
      let b3 = Int64.shift_left (Int64.of_int (bits s land 7)) 60 in
      let r = Int64.logor b1 (Int64.logor b2 b3) in
      let v = Int64.rem r n in
      if Int64.sub r v > Int64.add (Int64.sub Int64.max_int n) 1L
      then int64aux s n
      else v

    let int64 s bound =
      if bound <= 0L
      then invalid_arg "Random.int64"
      else int64aux s bound

    let nativeint =
      if Nativeint.size = 32
      then fun s bound -> Nativeint.of_int32 (int32 s (Nativeint.to_int32 bound))
      else fun s bound -> Int64.to_nativeint (int64 s (Int64.of_nativeint bound))

    let rawfloat s =
      let scale = 1073741824.0  (* 2^30 *)
      and r1 = Stdlib.float (bits s)
      and r2 = Stdlib.float (bits s)
      in (r1 /. scale +. r2) /. scale

    let float s bound = rawfloat s *. bound

    let bool s = (bits s land 1 = 0)
  end

  let bits () = State.bits B.default
  let int bound = State.int B.default bound
  let int32 bound = State.int32 B.default bound
  let nativeint bound = State.nativeint B.default bound
  let int64 bound = State.int64 B.default bound
  let float scale = State.float B.default scale
  let bool () = State.bool B.default

  let full_init seed = B.full_init B.default seed
  let init seed = B.full_init B.default [|seed|]
  let self_init () = full_init (random_seed ())

  let get_state () = State.copy B.default
  let set_state s = B.assign B.default s
end

(** {2 Functor for the Basic Interface}

   In case it is not possible to provide what the full interface asks for, one
   can only provide the bits function. Most of the functions of the Random
   module will still be provided. The ones manipulating the state will not. Note
   that this includes all the initialisation functions. *)

module type BASICBITS = sig
  val bits : unit -> int
end

module Basic (B : BASICBITS) : BASIC = struct
  include Full (struct
      type state = unit

      let new_state () = ()
      let assign () () = ()
      let full_init () _ = ()

      let bits = B.bits

      let default = ()
    end)
end
