/*

DO NOT edit this file

*/
#include "list.h"
#include "regions.h"
#include "banshee.h"
#include <assert.h>
#include <stdio.h>
#include "bool.h"
#include "ufind.h"
#include <string.h>
#include "hash.h"
#include "banshee_region_persist_kinds.h"
#include "setif-sort.h"
#include "term-sort.h"
#include "flowrow-sort.h"
#include "term-sort.h"

#define LAM_ 11
#define REF_ 12

typedef gen_e alabel_t;
typedef gen_e_list alabel_t_list;

typedef gen_e L;
typedef gen_e_list L_list;

typedef struct flowrow_field_ *argT_field;
typedef flowrow_map argT_map;
typedef gen_e argT;

typedef gen_e T;
typedef gen_e_list T_list;


stamp alabel_t_get_stamp (gen_e arg1);
bool alabel_t_is_var (gen_e arg1);
DECLARE_OPAQUE_LIST (alabel_t_list, gen_e);
alabel_t alabel_t_zero (void);
alabel_t alabel_t_one (void);
alabel_t alabel_t_wild (void);
alabel_t alabel_t_fresh (const char *name);
alabel_t alabel_t_fresh_large (const char *name);
alabel_t alabel_t_union (alabel_t_list exprs);
alabel_t alabel_t_inter (alabel_t_list exprs);
alabel_t alabel_t_constant (const char *name);
bool alabel_t_is_constant (alabel_t e, const char *name);
alabel_t_list alabel_t_tlb (alabel_t e);
void alabel_t_inclusion_ind (alabel_t e1, alabel_t e2);
void alabel_t_unify_ind (alabel_t e1, alabel_t e2);

void alabel_t_print (FILE * arg1, alabel_t arg2);
bool alabel_t_res_proj (setif_var arg1, gen_e arg2);
void alabel_t_con_match (gen_e arg1, gen_e arg2);
stamp L_get_stamp (gen_e arg1);
bool L_is_var (gen_e arg1);
DECLARE_OPAQUE_LIST (L_list, gen_e);
L L_zero (void);
L L_one (void);
L L_wild (void);
L L_fresh (const char *name);
L L_constant (const char *name);
bool L_is_constant (L e, const char *name);
L L_ecr (L e);
void L_inclusion_ind (L e1, L e2);
void L_cunify_ind (L e1, L e2);
void L_unify_ind (L e1, L e2);

L lam (alabel_t arg1, argT arg2, T arg3);
struct lam_decon lam_decon (L arg1);
struct lam_
{
  int type;
  stamp st;
  alabel_t f0;
  argT f1;
  T f2;
};
struct lam_decon
{
  alabel_t f0;
  argT f1;
  T f2;
};
void L_print (FILE * arg1, L arg2);
bool L_occurs (term_var arg1, L arg2);
void L_con_match (gen_e arg1, gen_e arg2);
stamp argT_get_stamp (gen_e arg1);
bool argT_is_var (gen_e arg1);
DECLARE_OPAQUE_LIST (argT_map, flowrow_field);
void argT_inclusion_ind (argT row1, argT row2);
void argT_unify_ind (argT row1, argT row2);
void argT_print (FILE * f, argT row);
stamp T_get_stamp (gen_e arg1);
bool T_is_var (gen_e arg1);
DECLARE_OPAQUE_LIST (T_list, gen_e);
T T_zero (void);
T T_one (void);
T T_wild (void);
T T_fresh (const char *name);
T T_constant (const char *name);
bool T_is_constant (T e, const char *name);
T T_ecr (T e);
void T_inclusion_ind (T e1, T e2);
void T_cunify_ind (T e1, T e2);
void T_unify_ind (T e1, T e2);

T ref (alabel_t arg1, T arg2, L arg3);
struct ref_decon ref_decon (T arg1);
struct ref_
{
  int type;
  stamp st;
  alabel_t f0;
  T f1;
  L f2;
};
struct ref_decon
{
  alabel_t f0;
  T f1;
  L f2;
};
void T_print (FILE * arg1, T arg2);
bool T_occurs (term_var arg1, T arg2);
void T_con_match (gen_e arg1, gen_e arg2);

stamp alabel_t_get_stamp (gen_e arg1)
{
  return setif_get_stamp ((gen_e) arg1);
}

bool alabel_t_is_var (gen_e arg1)
{
  return setif_is_var ((gen_e) arg1);
}

DEFINE_LIST (alabel_t_list, gen_e);
alabel_t alabel_t_zero (void)
{
  return setif_zero ();
}

alabel_t alabel_t_one (void)
{
  return setif_one ();
}

alabel_t alabel_t_wild (void)
{
  return setif_wild ();
}

alabel_t alabel_t_fresh (const char *name)
{
  return setif_fresh (name);
}

alabel_t alabel_t_fresh_small (const char *name)
{
  return setif_fresh_small (name);
}

alabel_t alabel_t_fresh_large (const char *name)
{
  return setif_fresh_large (name);
}

alabel_t alabel_t_union (alabel_t_list exprs)
{
  return setif_union (exprs);
}

alabel_t alabel_t_inter (alabel_t_list exprs)
{
  return setif_inter (exprs);
}

alabel_t alabel_t_constant (const char *name)
{
  return setif_constant (name);
}

bool alabel_t_eq (alabel_t e1, alabel_t e2)
{
  return setif_eq (e1, e2);
}

int alabel_t_cmp (const alabel_t e1, const alabel_t e2)
{
  return setif_get_stamp (e1) - setif_get_stamp (e2);
}

bool alabel_t_is_constant (alabel_t e, const char *name)
{
  if (setif_is_constant (e))
    if (!name)
      return TRUE;
    else
      return (!strcmp (name, setif_get_constant_name (e)));
  else
    return FALSE;
}

alabel_t_list alabel_t_tlb (alabel_t e)
{
  return setif_tlb (e);
}

void alabel_t_inclusion_ind (alabel_t e1, alabel_t e2)
{
  setif_inclusion (alabel_t_con_match, alabel_t_res_proj, alabel_t_print, e1,
		   e2);
}

void alabel_t_inclusion (alabel_t e1, alabel_t e2)
{
  banshee_clock_tick ();
  alabel_t_inclusion_ind (e1, e2);
}

void alabel_t_inclusion_ind_contra (alabel_t e1, alabel_t e2)
{
  setif_inclusion (alabel_t_con_match, alabel_t_res_proj, alabel_t_print, e2,
		   e1);
}

void alabel_t_unify_ind (alabel_t e1, alabel_t e2)
{
  setif_inclusion (alabel_t_con_match, alabel_t_res_proj, alabel_t_print, e1,
		   e2);
  setif_inclusion (alabel_t_con_match, alabel_t_res_proj, alabel_t_print, e2,
		   e1);
}

void alabel_t_unify (alabel_t e1, alabel_t e2)
{
  banshee_clock_tick ();
  alabel_t_unify_ind (e1, e2);
}

void alabel_t_print (FILE * arg1, alabel_t arg2)
{
  switch (((setif_term) arg2)->type)
    {
    case VAR_TYPE:
      fprintf (arg1, "%s::%ld", sv_get_name ((setif_var) arg2),
	       (long) sv_get_stamp ((setif_var) arg2));
      break;
    case ZERO_TYPE:
      fprintf (arg1, "0");
      break;
    case ONE_TYPE:
      fprintf (arg1, "1");
      break;
    case CONSTANT_TYPE:
      fprintf (arg1, "%s", setif_get_constant_name (arg2));
      break;
    case UNION_TYPE:
      {
	gen_e_list list = setif_get_union (arg2);
	gen_e_list_scanner scan;
	gen_e temp;
	gen_e_list_scan (list, &scan);
	if (gen_e_list_next (&scan, &temp))
	  alabel_t_print (arg1, temp);
	while (gen_e_list_next (&scan, &temp))
	  {
	    fprintf (arg1, " || ");
	    alabel_t_print (arg1, temp);
	  }

      }
      break;
    case INTER_TYPE:
      {
	gen_e_list list = setif_get_inter (arg2);
	gen_e_list_scanner scan;
	gen_e temp;
	gen_e_list_scan (list, &scan);
	if (gen_e_list_next (&scan, &temp))
	  alabel_t_print (arg1, temp);
	while (gen_e_list_next (&scan, &temp))
	  {
	    fprintf (arg1, " && ");
	    alabel_t_print (arg1, temp);
	  }

      }
      break;

    default:
      return;
    }

}

bool alabel_t_res_proj (setif_var arg1, gen_e arg2)
{
  switch (((setif_term) arg2)->type)
    {

    default:
      return FALSE;
    }

  return FALSE;
}

void alabel_t_con_match (gen_e arg1, gen_e arg2)
{
  switch (((setif_term) arg1)->type)
    {

    default:
      return;
    }

  return;
}

stamp L_get_stamp (gen_e arg1)
{
  return term_get_stamp ((gen_e) arg1);
}

bool L_is_var (gen_e arg1)
{
  return term_is_var ((gen_e) arg1);
}

DEFINE_LIST (L_list, gen_e);

L L_zero (void)
{
  return term_zero ();
}

L L_one (void)
{
  return term_one ();
}

L L_wild (void)
{
  return term_wild ();
}

L L_fresh (const char *name)
{
  return term_fresh (name);
}

L L_fresh_small (const char *name)
{
  return term_fresh_small (name);
}

L L_fresh_large (const char *name)
{
  return term_fresh_large (name);
}

L L_constant (const char *name)
{
  return term_constant (name);
}

bool L_is_constant (L e, const char *name)
{
  if (term_is_constant (e))
    return (!strcmp (name, term_get_constant_name (e)));
  else
    return FALSE;
}

L L_ecr (L e)
{
  return term_get_ecr (e);
}

void L_inclusion_ind (L e1, L e2)
{
  term_unify (L_con_match, L_occurs, e1, e2);
}

bool L_eq (L e1, L e2)
{
  return term_eq (e1, e2);
}

int L_cmp (const L e1, const L e2)
{
  return term_get_stamp (e1) - term_get_stamp (e2);
}

void L_inclusion_ind_contra (L e1, L e2)
{
  term_unify (L_con_match, L_occurs, e2, e1);
}

void L_unify (L e1, L e2)
{
  banshee_clock_tick ();
  L_unify_ind (e1, e2);
}

void L_cunify (L e1, L e2)
{
  banshee_clock_tick ();
  L_cunify_ind (e1, e2);
}

void L_cunify_ind (L e1, L e2)
{
  term_cunify (L_con_match, L_occurs, e1, e2);
}

void L_unify_ind (L e1, L e2)
{
  term_unify (L_con_match, L_occurs, e1, e2);
}

bool L_is_lam (L e)
{
  return ((gen_term) e)->type == 11;
}

L lam (alabel_t arg1, argT arg2, T arg3)
{
  struct lam_ *ret;
  stamp s[4];
  s[0] = LAM_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  s[2] = argT_get_stamp ((gen_e) arg2);
  s[3] = T_get_stamp ((gen_e) arg3);
  if ((ret = (struct lam_ *) term_hash_find (term_sort_hash, s, 4)) == NULL)
    {
      ret = ralloc (term_sort_region, struct lam_);
      ret->type = s[0];
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      ret->f1 = arg2;
      ret->f2 = arg3;
      term_hash_insert (term_sort_hash, (gen_e) ret, s, 4);
    }
  return (L) ret;
}

struct lam_decon lam_decon (L arg1)
{
  if (((gen_term) arg1)->type == LAM_)
    {
      struct lam_ *c = (struct lam_ *) arg1;
      return (struct lam_decon)
      {
      c->f0, c->f1, c->f2};

    }
  else
    return (struct lam_decon)
    {
    NULL, NULL, NULL};
}

void L_print (FILE * arg1, L arg2)
{
  gen_e ecr = term_get_ecr (arg2);
  switch (((gen_term) ecr)->type)
    {
    case VAR_TYPE:
      fprintf (arg1, "%s", tv_get_name ((term_var) ecr));
      break;
    case ZERO_TYPE:
      fprintf (arg1, "0");
      break;
    case ONE_TYPE:
      fprintf (arg1, "1");
      break;
    case CONSTANT_TYPE:
      fprintf (arg1, "%s", term_get_constant_name (ecr));
      break;
    case LAM_:
      {
	fprintf (arg1, "lam(");
	alabel_t_print (arg1, ((struct lam_ *) ecr)->f0);
	fprintf (arg1, ",");
	argT_print (arg1, ((struct lam_ *) ecr)->f1);
	fprintf (arg1, ",");
	T_print (arg1, ((struct lam_ *) ecr)->f2);
	fprintf (arg1, ")");

      }
      break;

    default:
      return;
    }

}

bool L_occurs (term_var arg1, L arg2)
{
  gen_e ecr = term_get_ecr (arg2);
  switch (((gen_term) ecr)->type)
    {
    case VAR_TYPE:
      return (term_get_stamp ((gen_e) arg1) == term_get_stamp (ecr));
      break;
    case LAM_:
      {
	struct lam_ *con = (struct lam_ *) arg2;
	return L_occurs (arg1, con->f0) || L_occurs (arg1, con->f1)
	  || L_occurs (arg1, con->f2);

      }
      break;

    default:
      return FALSE;
    }

}

void L_con_match (gen_e arg1, gen_e arg2)
{
  switch (((gen_term) arg1)->type)
    {
    case LAM_:
      switch (((gen_term) arg2)->type)
	{
	case LAM_:
	  {
	    alabel_t_unify_ind (((struct lam_ *) arg1)->f0,
				((struct lam_ *) arg2)->f0);
	    argT_unify_ind (((struct lam_ *) arg1)->f1,
			    ((struct lam_ *) arg2)->f1);
	    T_unify_ind (((struct lam_ *) arg1)->f2,
			 ((struct lam_ *) arg2)->f2);

	  }
	  break;

	default:
	  handle_error (arg1, arg2, bek_cons_mismatch);
	}

      break;

    default:
      handle_error (arg1, arg2, bek_cons_mismatch);
    }

  return;
}

stamp argT_get_stamp (gen_e arg1)
{
  return flowrow_get_stamp ((gen_e) arg1);
}

bool argT_is_var (gen_e arg1)
{
  return flowrow_is_var ((gen_e) arg1);
}

DEFINE_LIST (argT_map, flowrow_field);
argT_field argT_make_field (const char *label, T expr)
{
  flowrow_field result = ralloc (flowrow_region, struct flowrow_field_);
  result->label = rstrdup (banshee_nonptr_region, label);
  result->expr = (gen_e) expr;
  return result;
}

argT argT_zero (void)
{
  return flowrow_zero ();
}

argT argT_one (void)
{
  return flowrow_one ();
}

argT argT_abs (void)
{
  return flowrow_abs ();
}

argT argT_wild (void)
{
  return flowrow_wild ();
}

argT argT_fresh (const char *name)
{
  return flowrow_fresh (name);
}

argT argT_fresh_small (const char *name)
{
  return flowrow_fresh_small (name);
}

argT argT_fresh_large (const char *name)
{
  return flowrow_fresh_large (name);
}

argT argT_row (argT_map fields, argT rest)
{
  return flowrow_row (T_get_stamp, fields, rest);
}

T argT_extract_field (const char *field_name, argT row)
{
  return flowrow_extract_field (field_name, row);
}

argT argT_extract_rest (argT row)
{
  return flowrow_extract_rest (row);
}

bool argT_eq (argT row1, argT row2)
{
  return flowrow_eq (row1, row2);
}

int argT_cmp (const argT e1, const argT e2)
{
  return flowrow_get_stamp (e1) - flowrow_get_stamp (e2);
}

argT_map argT_extract_fields (argT row)
{
  return flowrow_extract_fields (row);
}

void argT_inclusion_ind (argT row1, argT row2)
{
  flowrow_inclusion (T_fresh, T_get_stamp, T_inclusion_ind, T_zero (), row1,
		     row2);
}

void argT_inclusion_ind_contra (argT row1, argT row2)
{
  flowrow_inclusion (T_fresh, T_get_stamp, T_inclusion_ind, T_zero (), row2,
		     row1);
}

void argT_unify_ind (argT row1, argT row2)
{
  argT_inclusion_ind (row1, row2);
  argT_inclusion_ind (row2, row1);
}

void argT_unify (argT row1, argT row2)
{
  banshee_clock_tick ();
  argT_unify_ind (row1, row2);
}

void argT_inclusion (argT row1, argT row2)
{
  banshee_clock_tick ();
  argT_inclusion_ind (row1, row2);
}

void argT_print (FILE * f, argT row)
{
  flowrow_print (f, T_get_stamp, T_print, row);
}

stamp T_get_stamp (gen_e arg1)
{
  return term_get_stamp ((gen_e) arg1);
}

bool T_is_var (gen_e arg1)
{
  return term_is_var ((gen_e) arg1);
}

DEFINE_LIST (T_list, gen_e);

T T_zero (void)
{
  return term_zero ();
}

T T_one (void)
{
  return term_one ();
}

T T_wild (void)
{
  return term_wild ();
}

T T_fresh (const char *name)
{
  return term_fresh (name);
}

T T_fresh_small (const char *name)
{
  return term_fresh_small (name);
}

T T_fresh_large (const char *name)
{
  return term_fresh_large (name);
}

T T_constant (const char *name)
{
  return term_constant (name);
}

bool T_is_constant (T e, const char *name)
{
  if (term_is_constant (e))
    return (!strcmp (name, term_get_constant_name (e)));
  else
    return FALSE;
}

T T_ecr (T e)
{
  return term_get_ecr (e);
}

void T_inclusion_ind (T e1, T e2)
{
  term_unify (T_con_match, T_occurs, e1, e2);
}

bool T_eq (T e1, T e2)
{
  return term_eq (e1, e2);
}

int T_cmp (const T e1, const T e2)
{
  return term_get_stamp (e1) - term_get_stamp (e2);
}

void T_inclusion_ind_contra (T e1, T e2)
{
  term_unify (T_con_match, T_occurs, e2, e1);
}

void T_unify (T e1, T e2)
{
  banshee_clock_tick ();
  T_unify_ind (e1, e2);
}

void T_cunify (T e1, T e2)
{
  banshee_clock_tick ();
  T_cunify_ind (e1, e2);
}

void T_cunify_ind (T e1, T e2)
{
  term_cunify (T_con_match, T_occurs, e1, e2);
}

void T_unify_ind (T e1, T e2)
{
  term_unify (T_con_match, T_occurs, e1, e2);
}

bool T_is_ref (T e)
{
  return ((gen_term) e)->type == 12;
}

T ref (alabel_t arg1, T arg2, L arg3)
{
  struct ref_ *ret;
  stamp s[4];
  s[0] = REF_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  s[2] = T_get_stamp ((gen_e) arg2);
  s[3] = L_get_stamp ((gen_e) arg3);
  if ((ret = (struct ref_ *) term_hash_find (term_sort_hash, s, 4)) == NULL)
    {
      ret = ralloc (term_sort_region, struct ref_);
      ret->type = s[0];
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      ret->f1 = arg2;
      ret->f2 = arg3;
      term_hash_insert (term_sort_hash, (gen_e) ret, s, 4);
    }
  return (T) ret;
}

struct ref_decon ref_decon (T arg1)
{
  if (((gen_term) arg1)->type == REF_)
    {
      struct ref_ *c = (struct ref_ *) arg1;
      return (struct ref_decon)
      {
      c->f0, c->f1, c->f2};

    }
  else
    return (struct ref_decon)
    {
    NULL, NULL, NULL};
}

void T_print (FILE * arg1, T arg2)
{
  gen_e ecr = term_get_ecr (arg2);
  switch (((gen_term) ecr)->type)
    {
    case VAR_TYPE:
      fprintf (arg1, "%s", tv_get_name ((term_var) ecr));
      break;
    case ZERO_TYPE:
      fprintf (arg1, "0");
      break;
    case ONE_TYPE:
      fprintf (arg1, "1");
      break;
    case CONSTANT_TYPE:
      fprintf (arg1, "%s", term_get_constant_name (ecr));
      break;
    case REF_:
      {
	fprintf (arg1, "ref(");
	alabel_t_print (arg1, ((struct ref_ *) ecr)->f0);
	fprintf (arg1, ",");
	T_print (arg1, ((struct ref_ *) ecr)->f1);
	fprintf (arg1, ",");
	L_print (arg1, ((struct ref_ *) ecr)->f2);
	fprintf (arg1, ")");

      }
      break;

    default:
      return;
    }

}

bool T_occurs (term_var arg1, T arg2)
{
  gen_e ecr = term_get_ecr (arg2);
  switch (((gen_term) ecr)->type)
    {
    case VAR_TYPE:
      return (term_get_stamp ((gen_e) arg1) == term_get_stamp (ecr));
      break;
    case REF_:
      {
	struct ref_ *con = (struct ref_ *) arg2;
	return T_occurs (arg1, con->f0) || T_occurs (arg1, con->f1)
	  || T_occurs (arg1, con->f2);

      }
      break;

    default:
      return FALSE;
    }

}

void T_con_match (gen_e arg1, gen_e arg2)
{
  switch (((gen_term) arg1)->type)
    {
    case REF_:
      switch (((gen_term) arg2)->type)
	{
	case REF_:
	  {
	    alabel_t_unify_ind (((struct ref_ *) arg1)->f0,
				((struct ref_ *) arg2)->f0);
	    T_unify_ind (((struct ref_ *) arg1)->f1,
			 ((struct ref_ *) arg2)->f1);
	    L_unify_ind (((struct ref_ *) arg1)->f2,
			 ((struct ref_ *) arg2)->f2);

	  }
	  break;

	default:
	  handle_error (arg1, arg2, bek_cons_mismatch);
	}

      break;

    default:
      handle_error (arg1, arg2, bek_cons_mismatch);
    }

  return;
}

void steensgaard_terms_init (void)
{
  engine_init ();
  setif_init ();
  term_init ();
  flowrow_init ();
  term_init ();
}

void steensgaard_terms_reset (void)
{
  engine_reset ();
  setif_reset ();
  term_reset ();
  flowrow_reset ();
  term_reset ();
}

void steensgaard_terms_stats (FILE * arg1)
{
  engine_stats (arg1);
}

void steensgaard_terms_print_graph (FILE * arg1)
{
  print_constraint_graphs (arg1);
}

void steensgaard_terms_serialize (FILE * arg1, hash_table * arg2,
				  unsigned long arg3)
{
  return;
}

hash_table *steensgaard_terms_deserialize (FILE * arg1)
{
  return NULL;
}

void steensgaard_terms_region_serialize (FILE * arg1)
{
  return;
}

void steensgaard_terms_region_deserialize (translation arg1, FILE * arg2)
{
  return;
}