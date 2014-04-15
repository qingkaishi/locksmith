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

val engspec :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Engspec.engspec
