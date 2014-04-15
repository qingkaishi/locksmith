(*
 *
 * Copyright (c) 2004-2007, 
 *  Polyvios Pratikakis <polyvios@cs.umd.edu>
 *  Michael Hicks       <mwh@cs.umd.edu>
 *  Jeff Foster         <jfoster@cs.umd.edu>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. The names of the contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *)
(*pp camlp4r *)

type handler =
    Alloc
  | Free
  | Newlock
  | Destroy
  | Acquire
  | Trylock
  | Release
  | Fork
  | Exit
  | Memcpy
  | Strcmp
  | Va_start
  | Va_arg
  | Memset
  | Pack
  | Start_unpack
  | End_unpack

let lexer =
  Genlex.make_lexer
    ["Locktype"; "Free"; "Alloc"; "Newlock"; "Destroy"; "Acquire"; "Trylock";
     "Release"; "Fork"; "Exit"; "Memcpy"; "Strcmp"; "Va_start"; "Va_arg";
     "Memset"; "Pack"; "Start_unpack"; "End_unpack"; ";"]


module Strmap = Lockutil.Strmap
open Genlex

let lock_type_names : string list ref =
  ref ["spinlock_t"; "pthread_mutex_t"; "sem_t"]
let special_functions : handler Strmap.t ref =
  ref
    (Strmap.add "pthread_mutex_init" Newlock
       (Strmap.add "spin_lock_init" Newlock
          (Strmap.add "sem_init" Newlock
             (Strmap.add "sem_wait" Acquire
                (Strmap.add "sem_post" Release
                   (Strmap.add "pthread_mutex_lock" Acquire
                      (Strmap.add "pthread_mutex_unlock" Release
                         (Strmap.add "_spin_lock_irqsave" Acquire
                            (Strmap.add "_spin_unlock_irqrestore" Release
                               (Strmap.add "_spin_lock" Acquire
                                  (Strmap.add "_spin_unlock" Release
                                     (Strmap.add "_spin_lock_bh" Acquire
                                        (Strmap.add "_spin_unlock_bh" Release
                                           (Strmap.add "_spin_lock_irq"
                                              Acquire
                                              (Strmap.add "_spin_unlock_irq"
                                                 Release
                                                 (Strmap.add "_read_lock"
                                                    Acquire
                                                    (Strmap.add "_read_unlock"
                                                       Release
                                                       (Strmap.add
                                                          "_read_lock_bh"
                                                          Acquire
                                                          (Strmap.add "_read_unlock_bh"
                                                             Release
                                                             (Strmap.add "_read_lock_irq"
                                                                Acquire
                                                                (Strmap.add "_read_unlock_irq"
                                                                   Release
                                                                   (Strmap.add "_read_lock_irqsave"
                                                                      Acquire
                                                                      (Strmap.
                                                                         add
                                                                         "_read_unlock_irqrestore" Release
                                                                         (Strmap.add "_write_lock" Acquire (Strmap.add "_write_unlock" Release (Strmap.add "_write_lock_bh" Acquire (Strmap.add "_write_unlock_bh" Release (Strmap.add "_write_lock_irq" Acquire (Strmap.add "_write_unlock_irq" Release (Strmap.add "_write_lock_irqsave" Acquire (Strmap.add "_write_unlock_irqrestore" Release (Strmap.add "pthread_mutex_trylock" Trylock (Strmap.add "pthread_mutex_destroy" Destroy (Strmap.add "pthread_create" Fork (Strmap.add "pthread_exit" Exit (Strmap.add "exit" Exit (Strmap.add "pack" Pack (Strmap.add "start_unpack" Start_unpack (Strmap.add "end_unpack" End_unpack (Strmap.add "kmalloc" Alloc (Strmap.add "malloc" Alloc (Strmap.add "free" Free (Strmap.add "realloc" Alloc (Strmap.add "calloc" Alloc (Strmap.add "__builtin_alloca" Alloc (Strmap.add "xalloc" Alloc (Strmap.add "memcpy" Memcpy (Strmap.add "bcopy" Memcpy (Strmap.add "memmove" Memcpy (Strmap.add "__builtin_memcpy" Memcpy (Strmap.add "__memcpy" Memcpy (Strmap.add "strcpy" Memcpy (Strmap.add "strncpy" Memcpy (Strmap.add "__builtin_strcpy" Memcpy (Strmap.add "__builtin_strncpy" Memcpy (Strmap.add "__constant_memcpy" Memcpy (Strmap.add "__builtin_memset" Memset (Strmap.add "__builtin_strcmp" Strcmp (Strmap.add "__builtin_memcmp" Strcmp (Strmap.add "__builtin_strncmp" Strcmp (Strmap.add "strncmp" Strcmp (Strmap.add "strcmp" Strcmp (Strmap.add "__builtin_va_start" Va_start (Strmap.add "va_start" Va_start (Strmap.add "stdarg_start" Va_start (Strmap.add "__builtin_stdarg_start" Va_start (Strmap.add "memset" Memset (Strmap.add "__memset_generic" Memset Strmap.empty))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

let add_to_sf h s = special_functions := Strmap.add s h !special_functions

let add_to_lt s = lock_type_names := s :: !lock_type_names

let parse_entry (strm__ : _ Stream.t) =
  match Stream.peek strm__ with
    Some (Kwd "Locktype") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_lt x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Alloc") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Alloc x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Free") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Free x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Newlock") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Newlock x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Destroy") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Destroy x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Acquire") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Acquire x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Trylock") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Trylock x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Release") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Release x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Fork") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Fork x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Exit") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Exit x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Memcpy") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Memcpy x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Strcmp") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Strcmp x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Va_start") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Va_start x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Va_arg") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Va_arg x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Memset") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Memset x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Start_unpack") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Start_unpack x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "End_unpack") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf End_unpack x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd "Pack") ->
      Stream.junk strm__;
      begin match Stream.peek strm__ with
        Some (Ident x) ->
          Stream.junk strm__;
          begin match Stream.peek strm__ with
            Some (Kwd ";") -> Stream.junk strm__; add_to_sf Pack x
          | _ -> raise (Stream.Error "")
          end
      | _ -> raise (Stream.Error "")
      end
  | Some (Kwd ";") -> Stream.junk strm__; ()
  | _ -> ()

let rec parse_stream s =
  match Stream.peek s with
    None -> ()
  | Some _ -> parse_entry (lexer s); parse_stream s

let parse_settings filename =
  let f = open_in filename in
  let s = Stream.of_channel f in parse_stream s; close_in f

let options =
  ["--locksmith-settings",
   Arg.String
     (fun filename ->
        lock_type_names := [];
        special_functions := Strmap.empty;
        parse_settings filename),
   " Load a separate settings file instead of defaults."]

