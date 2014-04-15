type token =
  | EOF
  | IDENT of (string)
  | SORT of (Engspec.sort_gen)
  | POS
  | NEG
  | OR
  | COLON
  | EQ
  | LPAREN
  | RPAREN
  | CROSS
  | LANGLE
  | RANGLE
  | SPECIFICATION
  | SPEC
  | END
  | DATA
  | OF
  | AND

open Parsing;;
# 34 "parser.mly"
open Engspec
let r x = List.rev x
# 27 "parser.ml"
let yytransl_const = [|
    0 (* EOF *);
  259 (* POS *);
  260 (* NEG *);
  261 (* OR *);
  262 (* COLON *);
  263 (* EQ *);
  264 (* LPAREN *);
  265 (* RPAREN *);
  266 (* CROSS *);
  267 (* LANGLE *);
  268 (* RANGLE *);
  269 (* SPECIFICATION *);
  270 (* SPEC *);
  271 (* END *);
  272 (* DATA *);
  273 (* OF *);
  274 (* AND *);
    0|]

let yytransl_block = [|
  257 (* IDENT *);
  258 (* SORT *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\003\000\003\000\004\000\004\000\005\000\
\006\000\006\000\007\000\007\000\008\000\008\000\008\000\009\000\
\009\000\010\000\010\000\010\000\000\000"

let yylen = "\002\000\
\009\000\001\000\002\000\005\000\006\000\001\000\002\000\005\000\
\000\000\002\000\001\000\003\000\003\000\001\000\006\000\001\000\
\003\000\002\000\002\000\001\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\000\000\021\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\002\000\000\000\000\000\003\000\000\000\
\001\000\000\000\000\000\000\000\000\000\000\000\011\000\000\000\
\000\000\006\000\000\000\000\000\000\000\000\000\007\000\000\000\
\020\000\000\000\000\000\000\000\016\000\012\000\000\000\000\000\
\018\000\019\000\000\000\000\000\000\000\017\000\008\000\000\000"

let yydgoto = "\002\000\
\004\000\011\000\012\000\025\000\026\000\020\000\022\000\023\000\
\036\000\037\000"

let yysindex = "\001\000\
\252\254\000\000\023\255\000\000\006\255\027\255\009\255\022\255\
\004\255\036\255\015\255\000\000\032\255\039\000\000\000\038\255\
\000\000\034\255\041\255\025\255\246\254\039\255\000\000\044\255\
\025\255\000\000\045\255\002\255\041\255\042\255\000\000\035\255\
\000\000\048\255\049\255\043\255\000\000\000\000\050\255\037\255\
\000\000\000\000\002\255\034\255\002\255\000\000\000\000\043\255"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\007\255\000\000\017\255\251\254\011\255\000\000\000\000\
\019\255\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\255\254\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\007\255\000\000\000\000\000\000\003\255"

let yygindex = "\000\000\
\000\000\000\000\040\000\000\000\030\000\012\000\000\000\028\000\
\013\000\016\000"

let yytablesize = 59
let yytable = "\014\000\
\027\000\001\000\033\000\013\000\034\000\035\000\028\000\015\000\
\003\000\014\000\014\000\006\000\014\000\013\000\013\000\008\000\
\013\000\015\000\015\000\010\000\015\000\009\000\009\000\005\000\
\009\000\010\000\010\000\007\000\010\000\014\000\010\000\004\000\
\004\000\005\000\005\000\009\000\013\000\016\000\017\000\018\000\
\019\000\021\000\024\000\029\000\030\000\032\000\040\000\039\000\
\041\000\042\000\015\000\044\000\043\000\045\000\031\000\047\000\
\038\000\048\000\046\000"

let yycheck = "\005\001\
\011\001\001\000\001\001\005\001\003\001\004\001\017\001\005\001\
\013\001\015\001\016\001\006\001\018\001\015\001\016\001\007\001\
\018\001\015\001\016\001\016\001\018\001\015\001\016\001\001\001\
\018\001\015\001\016\001\001\001\018\001\015\001\016\001\015\001\
\016\001\015\001\016\001\014\001\001\001\006\001\000\000\002\001\
\007\001\001\001\018\001\005\001\001\001\001\001\012\001\006\001\
\001\001\001\001\011\000\002\001\010\001\017\001\025\000\044\000\
\029\000\045\000\043\000"

let yynames_const = "\
  EOF\000\
  POS\000\
  NEG\000\
  OR\000\
  COLON\000\
  EQ\000\
  LPAREN\000\
  RPAREN\000\
  CROSS\000\
  LANGLE\000\
  RANGLE\000\
  SPECIFICATION\000\
  SPEC\000\
  END\000\
  DATA\000\
  OF\000\
  AND\000\
  "

let yynames_block = "\
  IDENT\000\
  SORT\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 7 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _7 = (Parsing.peek_val __caml_parser_env 2 : Engspec.dataspec list) in
    Obj.repr(
# 57 "parser.mly"
                                                                ((_2,_4,r _7) )
# 150 "parser.ml"
               : Engspec.engspec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Engspec.dataspec) in
    Obj.repr(
# 60 "parser.mly"
                         ( [_1] )
# 157 "parser.ml"
               : Engspec.dataspec list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Engspec.dataspec list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Engspec.dataspec) in
    Obj.repr(
# 61 "parser.mly"
                                 ( (r _2)::_1 )
# 165 "parser.ml"
               : Engspec.dataspec list))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Engspec.sort_gen) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Engspec.databody) in
    Obj.repr(
# 65 "parser.mly"
                                               ( [(_2,_4,_5)] )
# 174 "parser.ml"
               : Engspec.dataspec))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : Engspec.sort_gen) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Engspec.databody) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Engspec.dataspec) in
    Obj.repr(
# 66 "parser.mly"
                                                            ( (_2,_4,_5)::_6)
# 184 "parser.ml"
               : Engspec.dataspec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Engspec.exprid * Engspec.sort_gen * Engspec.databody) in
    Obj.repr(
# 70 "parser.mly"
                  ( [_1] )
# 191 "parser.ml"
               : Engspec.dataspec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Engspec.dataspec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Engspec.exprid * Engspec.sort_gen * Engspec.databody) in
    Obj.repr(
# 71 "parser.mly"
                               ( _2::_1 )
# 199 "parser.ml"
               : Engspec.dataspec))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Engspec.sort_gen) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Engspec.databody) in
    Obj.repr(
# 75 "parser.mly"
                                              ( (_2,_4,_5) )
# 208 "parser.ml"
               : Engspec.exprid * Engspec.sort_gen * Engspec.databody))
; (fun __caml_parser_env ->
    Obj.repr(
# 79 "parser.mly"
                        ( [] )
# 214 "parser.ml"
               : Engspec.databody))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Engspec.databody) in
    Obj.repr(
# 80 "parser.mly"
                 ( r _2  )
# 221 "parser.ml"
               : Engspec.databody))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Engspec.conid * Engspec.consig option) in
    Obj.repr(
# 84 "parser.mly"
                ( [_1] )
# 228 "parser.ml"
               : Engspec.databody))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Engspec.databody) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Engspec.conid * Engspec.consig option) in
    Obj.repr(
# 85 "parser.mly"
                    ( _3::_1 )
# 236 "parser.ml"
               : Engspec.databody))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Engspec.bconsig list) in
    Obj.repr(
# 89 "parser.mly"
                   ( ((_1, false, None),Some (r _3) ) )
# 244 "parser.ml"
               : Engspec.conid * Engspec.consig option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 90 "parser.mly"
                   ( ((_1, false, None),None) )
# 251 "parser.ml"
               : Engspec.conid * Engspec.consig option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Engspec.bconsig list) in
    Obj.repr(
# 91 "parser.mly"
                                       ( ((_3, true, Some _1),Some (r _6) ) )
# 260 "parser.ml"
               : Engspec.conid * Engspec.consig option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Engspec.bconsig) in
    Obj.repr(
# 94 "parser.mly"
                  ( [_1] )
# 267 "parser.ml"
               : Engspec.bconsig list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Engspec.bconsig list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Engspec.bconsig) in
    Obj.repr(
# 95 "parser.mly"
                        ( _3::_1 )
# 275 "parser.ml"
               : Engspec.bconsig list))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 99 "parser.mly"
             ( (_2,POSvariance) )
# 282 "parser.ml"
               : Engspec.bconsig))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 100 "parser.mly"
             ( (_2,NEGvariance)  )
# 289 "parser.ml"
               : Engspec.bconsig))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 101 "parser.mly"
                ( (_1,NOvariance)  )
# 296 "parser.ml"
               : Engspec.bconsig))
(* Entry engspec *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let engspec (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Engspec.engspec)
