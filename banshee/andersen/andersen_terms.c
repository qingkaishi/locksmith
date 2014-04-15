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
#include "flowrow-sort.h"
#include "setif-sort.h"

#define REF_ 11
#define REFPROJ0_ 12
#define REFPROJ1_ 13
#define REFPROJ2_ 14
#define LAM_ 15
#define LAMPROJ0_ 16
#define LAMPROJ1_ 17
#define LAMPROJ2_ 18

typedef gen_e alabel_t;
typedef gen_e_list alabel_t_list;

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
T T_fresh_large (const char *name);
T T_union (T_list exprs);
T T_inter (T_list exprs);
T T_constant (const char *name);
bool T_is_constant (T e, const char *name);
T_list T_tlb (T e);
void T_inclusion_ind (T e1, T e2);
void T_unify_ind (T e1, T e2);

T ref (alabel_t arg1, T arg2, T arg3);
struct ref_decon ref_decon (T arg1);
struct ref_
{
  int type;
  stamp st;
  alabel_t f0;
  T f1;
  T f2;
};
struct ref_decon
{
  alabel_t f0;
  T f1;
  T f2;
};
struct refProj0_
{
  int type;
  stamp st;
  alabel_t f0;
};
gen_e ref_pat0_con (gen_e arg1);
T ref_pat0 (alabel_t arg1);
struct refProj1_
{
  int type;
  stamp st;
  T f0;
};
gen_e ref_pat1_con (gen_e arg1);
T ref_pat1 (T arg1);
struct refProj2_
{
  int type;
  stamp st;
  T f0;
};
gen_e ref_pat2_con (gen_e arg1);
T ref_pat2 (T arg1);
T lam (alabel_t arg1, argT arg2, T arg3);
struct lam_decon lam_decon (T arg1);
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
struct lamProj0_
{
  int type;
  stamp st;
  alabel_t f0;
};
gen_e lam_pat0_con (gen_e arg1);
T lam_pat0 (alabel_t arg1);
struct lamProj1_
{
  int type;
  stamp st;
  argT f0;
};
gen_e lam_pat1_con (gen_e arg1);
T lam_pat1 (argT arg1);
struct lamProj2_
{
  int type;
  stamp st;
  T f0;
};
gen_e lam_pat2_con (gen_e arg1);
T lam_pat2 (T arg1);
void T_print (FILE * arg1, T arg2);
bool T_res_proj (setif_var arg1, gen_e arg2);
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
  return setif_get_stamp ((gen_e) arg1);
}

bool T_is_var (gen_e arg1)
{
  return setif_is_var ((gen_e) arg1);
}

DEFINE_LIST (T_list, gen_e);
T T_zero (void)
{
  return setif_zero ();
}

T T_one (void)
{
  return setif_one ();
}

T T_wild (void)
{
  return setif_wild ();
}

T T_fresh (const char *name)
{
  return setif_fresh (name);
}

T T_fresh_small (const char *name)
{
  return setif_fresh_small (name);
}

T T_fresh_large (const char *name)
{
  return setif_fresh_large (name);
}

T T_union (T_list exprs)
{
  return setif_union (exprs);
}

T T_inter (T_list exprs)
{
  return setif_inter (exprs);
}

T T_constant (const char *name)
{
  return setif_constant (name);
}

bool T_eq (T e1, T e2)
{
  return setif_eq (e1, e2);
}

int T_cmp (const T e1, const T e2)
{
  return setif_get_stamp (e1) - setif_get_stamp (e2);
}

bool T_is_constant (T e, const char *name)
{
  if (setif_is_constant (e))
    if (!name)
      return TRUE;
    else
      return (!strcmp (name, setif_get_constant_name (e)));
  else
    return FALSE;
}

T_list T_tlb (T e)
{
  return setif_tlb (e);
}

void T_inclusion_ind (T e1, T e2)
{
  setif_inclusion (T_con_match, T_res_proj, T_print, e1, e2);
}

void T_inclusion (T e1, T e2)
{
  banshee_clock_tick ();
  T_inclusion_ind (e1, e2);
}

void T_inclusion_ind_contra (T e1, T e2)
{
  setif_inclusion (T_con_match, T_res_proj, T_print, e2, e1);
}

void T_unify_ind (T e1, T e2)
{
  setif_inclusion (T_con_match, T_res_proj, T_print, e1, e2);
  setif_inclusion (T_con_match, T_res_proj, T_print, e2, e1);
}

void T_unify (T e1, T e2)
{
  banshee_clock_tick ();
  T_unify_ind (e1, e2);
}

bool T_is_ref (T e)
{
  return ((setif_term) e)->type == 11;
}

T ref (alabel_t arg1, T arg2, T arg3)
{
  struct ref_ *ret;
  stamp s[4];
  s[0] = REF_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  s[2] = T_get_stamp ((gen_e) arg2);
  s[3] = T_get_stamp ((gen_e) arg3);
  if ((ret = (struct ref_ *) term_hash_find (setif_hash, s, 4)) == NULL)
    {
      ret = ralloc (permanent, struct ref_);
      ret->type = s[0];
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      ret->f1 = arg2;
      ret->f2 = arg3;
      term_hash_insert (setif_hash, (gen_e) ret, s, 4);
    }
  return (T) ret;
}

struct ref_decon ref_decon (T arg1)
{
  if (((setif_term) arg1)->type == REF_)
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

gen_e get_ref_proj0_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == REFPROJ0_)
	return (gen_e) ((struct refProj0_ *) temp)->f0;
    }
  return NULL;
}

alabel_t ref_proj0 (T arg1)
{
  alabel_t c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (alabel_t) sv_get_ub_proj (v, get_ref_proj0_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = alabel_t_fresh (NULL);
	  e = ref_pat0 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == REF_)
    return ((struct ref_ *) arg1)->f0;
  else if (setif_is_zero (arg1))
    return alabel_t_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_ref_proj0_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = alabel_t_fresh (NULL);
	  e = ref_pat0 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = alabel_t_fresh (NULL);
      e = ref_pat0 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e ref_pat0_con (gen_e arg1)
{
  return (gen_e) ref_pat0 ((alabel_t) arg1);
}

T ref_pat0 (alabel_t arg1)
{
  struct refProj0_ *ret;
  stamp s[2];
  s[0] = REFPROJ0_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  if ((ret = (struct refProj0_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct refProj0_);
      ret->type = REFPROJ0_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

gen_e get_ref_proj1_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == REFPROJ1_)
	return (gen_e) ((struct refProj1_ *) temp)->f0;
    }
  return NULL;
}

T ref_proj1 (T arg1)
{
  T c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (T) sv_get_ub_proj (v, get_ref_proj1_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = T_fresh (NULL);
	  e = ref_pat1 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == REF_)
    return ((struct ref_ *) arg1)->f1;
  else if (setif_is_zero (arg1))
    return T_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_ref_proj1_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = T_fresh (NULL);
	  e = ref_pat1 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = T_fresh (NULL);
      e = ref_pat1 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e ref_pat1_con (gen_e arg1)
{
  return (gen_e) ref_pat1 ((T) arg1);
}

T ref_pat1 (T arg1)
{
  struct refProj1_ *ret;
  stamp s[2];
  s[0] = REFPROJ1_;
  s[1] = T_get_stamp ((gen_e) arg1);
  if ((ret = (struct refProj1_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct refProj1_);
      ret->type = REFPROJ1_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

gen_e get_ref_proj2_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == REFPROJ2_)
	return (gen_e) ((struct refProj2_ *) temp)->f0;
    }
  return NULL;
}

T ref_proj2 (T arg1)
{
  T c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (T) sv_get_ub_proj (v, get_ref_proj2_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = T_fresh (NULL);
	  e = ref_pat2 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == REF_)
    return ((struct ref_ *) arg1)->f2;
  else if (setif_is_zero (arg1))
    return T_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_ref_proj2_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = T_fresh (NULL);
	  e = ref_pat2 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = T_fresh (NULL);
      e = ref_pat2 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e ref_pat2_con (gen_e arg1)
{
  return (gen_e) ref_pat2 ((T) arg1);
}

T ref_pat2 (T arg1)
{
  struct refProj2_ *ret;
  stamp s[2];
  s[0] = REFPROJ2_;
  s[1] = T_get_stamp ((gen_e) arg1);
  if ((ret = (struct refProj2_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct refProj2_);
      ret->type = REFPROJ2_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

bool T_is_lam (T e)
{
  return ((setif_term) e)->type == 15;
}

T lam (alabel_t arg1, argT arg2, T arg3)
{
  struct lam_ *ret;
  stamp s[4];
  s[0] = LAM_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  s[2] = argT_get_stamp ((gen_e) arg2);
  s[3] = T_get_stamp ((gen_e) arg3);
  if ((ret = (struct lam_ *) term_hash_find (setif_hash, s, 4)) == NULL)
    {
      ret = ralloc (permanent, struct lam_);
      ret->type = s[0];
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      ret->f1 = arg2;
      ret->f2 = arg3;
      term_hash_insert (setif_hash, (gen_e) ret, s, 4);
    }
  return (T) ret;
}

struct lam_decon lam_decon (T arg1)
{
  if (((setif_term) arg1)->type == LAM_)
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

gen_e get_lam_proj0_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == LAMPROJ0_)
	return (gen_e) ((struct lamProj0_ *) temp)->f0;
    }
  return NULL;
}

alabel_t lam_proj0 (T arg1)
{
  alabel_t c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (alabel_t) sv_get_ub_proj (v, get_lam_proj0_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = alabel_t_fresh (NULL);
	  e = lam_pat0 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == LAM_)
    return ((struct lam_ *) arg1)->f0;
  else if (setif_is_zero (arg1))
    return alabel_t_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_lam_proj0_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = alabel_t_fresh (NULL);
	  e = lam_pat0 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = alabel_t_fresh (NULL);
      e = lam_pat0 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e lam_pat0_con (gen_e arg1)
{
  return (gen_e) lam_pat0 ((alabel_t) arg1);
}

T lam_pat0 (alabel_t arg1)
{
  struct lamProj0_ *ret;
  stamp s[2];
  s[0] = LAMPROJ0_;
  s[1] = alabel_t_get_stamp ((gen_e) arg1);
  if ((ret = (struct lamProj0_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct lamProj0_);
      ret->type = LAMPROJ0_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

gen_e get_lam_proj1_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == LAMPROJ1_)
	return (gen_e) ((struct lamProj1_ *) temp)->f0;
    }
  return NULL;
}

argT lam_proj1 (T arg1)
{
  argT c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (argT) sv_get_ub_proj (v, get_lam_proj1_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = argT_fresh (NULL);
	  e = lam_pat1 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == LAM_)
    return ((struct lam_ *) arg1)->f1;
  else if (setif_is_zero (arg1))
    return argT_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_lam_proj1_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = argT_fresh (NULL);
	  e = lam_pat1 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = argT_fresh (NULL);
      e = lam_pat1 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e lam_pat1_con (gen_e arg1)
{
  return (gen_e) lam_pat1 ((argT) arg1);
}

T lam_pat1 (argT arg1)
{
  struct lamProj1_ *ret;
  stamp s[2];
  s[0] = LAMPROJ1_;
  s[1] = argT_get_stamp ((gen_e) arg1);
  if ((ret = (struct lamProj1_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct lamProj1_);
      ret->type = LAMPROJ1_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

gen_e get_lam_proj2_arg (gen_e_list arg1)
{
  gen_e temp;
  gen_e_list_scanner scan;
  gen_e_list_scan (arg1, &scan);
  while (gen_e_list_next (&scan, &temp))
    {
      if (((setif_term) temp)->type == LAMPROJ2_)
	return (gen_e) ((struct lamProj2_ *) temp)->f0;
    }
  return NULL;
}

T lam_proj2 (T arg1)
{
  T c;
  banshee_clock_tick ();
  if (setif_is_var (arg1))
    {
      setif_var v = (setif_var) arg1;
      c = (T) sv_get_ub_proj (v, get_lam_proj2_arg);
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  gen_e lb;
	  bounds_scanner scan;
	  c = T_fresh (NULL);
	  e = lam_pat2 (c);
	  sv_add_ub_proj (v, e);
	  if (!banshee_check_rollback (setif_sort))
	    {
	      setif_register_rollback ();
	    }
	  setif_register_ub_proj (sv_get_ub_projs (v), e);
	  bounds_scan (sv_get_lbs (v), &scan);
	  while (bounds_next (&scan, &lb))
	    {
	      setif_inclusion (T_con_match, T_res_proj, T_print, lb, e);
	    }
	  return c;
	}
    }
  else if (((setif_term) arg1)->type == LAM_)
    return ((struct lam_ *) arg1)->f2;
  else if (setif_is_zero (arg1))
    return T_zero ();
  else if (setif_is_union (arg1))
    {
      c = get_lam_proj2_arg (setif_get_proj_cache (arg1));
      if (c != NULL)
	return c;
      else
	{
	  T e;
	  c = T_fresh (NULL);
	  e = lam_pat2 (c);
	  setif_set_proj_cache (arg1, e);
	  T_inclusion_ind (arg1, e);
	  return c;
	}
    }
  else
    {
      T e;
      c = T_fresh (NULL);
      e = lam_pat2 (c);
      T_inclusion_ind (arg1, e);
      return c;
    }
}

gen_e lam_pat2_con (gen_e arg1)
{
  return (gen_e) lam_pat2 ((T) arg1);
}

T lam_pat2 (T arg1)
{
  struct lamProj2_ *ret;
  stamp s[2];
  s[0] = LAMPROJ2_;
  s[1] = T_get_stamp ((gen_e) arg1);
  if ((ret = (struct lamProj2_ *) term_hash_find (setif_hash, s, 2)) == NULL)
    {
      ret = ralloc (permanent, struct lamProj2_);
      ret->type = LAMPROJ2_;
      ret->st = stamp_fresh ();
      ret->f0 = arg1;
      term_hash_insert (setif_hash, (gen_e) ret, s, 2);
    }
  return (T) ret;
}

void T_print (FILE * arg1, T arg2)
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
	  T_print (arg1, temp);
	while (gen_e_list_next (&scan, &temp))
	  {
	    fprintf (arg1, " || ");
	    T_print (arg1, temp);
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
	  T_print (arg1, temp);
	while (gen_e_list_next (&scan, &temp))
	  {
	    fprintf (arg1, " && ");
	    T_print (arg1, temp);
	  }

      }
      break;
    case REF_:
      {
	fprintf (arg1, "ref(");
	alabel_t_print (arg1, ((struct ref_ *) arg2)->f0);
	fprintf (arg1, ",");
	T_print (arg1, ((struct ref_ *) arg2)->f1);
	fprintf (arg1, ",");
	T_print (arg1, ((struct ref_ *) arg2)->f2);
	fprintf (arg1, ")");

      }
      break;
    case LAM_:
      {
	fprintf (arg1, "lam(");
	alabel_t_print (arg1, ((struct lam_ *) arg2)->f0);
	fprintf (arg1, ",");
	argT_print (arg1, ((struct lam_ *) arg2)->f1);
	fprintf (arg1, ",");
	T_print (arg1, ((struct lam_ *) arg2)->f2);
	fprintf (arg1, ")");

      }
      break;
    case REFPROJ0_:
      {
	fprintf (arg1, "Proj[ref,0,");
	alabel_t_print (arg1, ((struct refProj0_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;
    case REFPROJ1_:
      {
	fprintf (arg1, "Proj[ref,1,");
	T_print (arg1, ((struct refProj1_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;
    case REFPROJ2_:
      {
	fprintf (arg1, "Proj[ref,2,");
	T_print (arg1, ((struct refProj2_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;
    case LAMPROJ0_:
      {
	fprintf (arg1, "Proj[lam,0,");
	alabel_t_print (arg1, ((struct lamProj0_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;
    case LAMPROJ1_:
      {
	fprintf (arg1, "Proj[lam,1,");
	argT_print (arg1, ((struct lamProj1_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;
    case LAMPROJ2_:
      {
	fprintf (arg1, "Proj[lam,2,");
	T_print (arg1, ((struct lamProj2_ *) arg2)->f0);
	fprintf (arg1, "]");

      }
      break;

    default:
      return;
    }

}

bool T_res_proj (setif_var arg1, gen_e arg2)
{
  switch (((setif_term) arg2)->type)
    {
    case REFPROJ0_:
      return setif_proj_merge (arg1, (gen_e) ((struct refProj0_ *) arg2)->f0,
			       get_ref_proj0_arg, ref_pat0_con,
			       (fresh_large_fn_ptr) alabel_t_fresh_large,
			       (incl_fn_ptr) alabel_t_inclusion_ind,
			       T_inclusion_ind);
      break;
    case REFPROJ1_:
      return setif_proj_merge (arg1, (gen_e) ((struct refProj1_ *) arg2)->f0,
			       get_ref_proj1_arg, ref_pat1_con,
			       (fresh_large_fn_ptr) T_fresh_large,
			       (incl_fn_ptr) T_inclusion_ind_contra,
			       T_inclusion_ind);
      break;
    case REFPROJ2_:
      return setif_proj_merge (arg1, (gen_e) ((struct refProj2_ *) arg2)->f0,
			       get_ref_proj2_arg, ref_pat2_con,
			       (fresh_large_fn_ptr) T_fresh_large,
			       (incl_fn_ptr) T_inclusion_ind,
			       T_inclusion_ind);
      break;
    case LAMPROJ0_:
      return setif_proj_merge (arg1, (gen_e) ((struct lamProj0_ *) arg2)->f0,
			       get_lam_proj0_arg, lam_pat0_con,
			       (fresh_large_fn_ptr) alabel_t_fresh_large,
			       (incl_fn_ptr) alabel_t_inclusion_ind,
			       T_inclusion_ind);
      break;
    case LAMPROJ1_:
      return setif_proj_merge (arg1, (gen_e) ((struct lamProj1_ *) arg2)->f0,
			       get_lam_proj1_arg, lam_pat1_con,
			       (fresh_large_fn_ptr) argT_fresh_large,
			       (incl_fn_ptr) argT_inclusion_ind_contra,
			       T_inclusion_ind);
      break;
    case LAMPROJ2_:
      return setif_proj_merge (arg1, (gen_e) ((struct lamProj2_ *) arg2)->f0,
			       get_lam_proj2_arg, lam_pat2_con,
			       (fresh_large_fn_ptr) T_fresh_large,
			       (incl_fn_ptr) T_inclusion_ind,
			       T_inclusion_ind);
      break;

    default:
      return FALSE;
    }

  return FALSE;
}

void T_con_match (gen_e arg1, gen_e arg2)
{
  switch (((setif_term) arg1)->type)
    {
    case REF_:
      switch (((setif_term) arg2)->type)
	{
	case REF_:
	  {
	    alabel_t_inclusion_ind (((struct ref_ *) arg1)->f0,
				    ((struct ref_ *) arg2)->f0);
	    T_inclusion_ind_contra (((struct ref_ *) arg1)->f1,
				    ((struct ref_ *) arg2)->f1);
	    T_inclusion_ind (((struct ref_ *) arg1)->f2,
			     ((struct ref_ *) arg2)->f2);

	  }
	  break;
	case REFPROJ0_:
	  alabel_t_inclusion_ind (((struct ref_ *) arg1)->f0,
				  ((struct refProj0_ *) arg2)->f0);
	  break;
	case REFPROJ1_:
	  T_inclusion_ind_contra (((struct ref_ *) arg1)->f1,
				  ((struct refProj1_ *) arg2)->f0);
	  break;
	case REFPROJ2_:
	  T_inclusion_ind (((struct ref_ *) arg1)->f2,
			   ((struct refProj2_ *) arg2)->f0);
	  break;
	case LAMPROJ0_:
	  return;
	  break;
	case LAMPROJ1_:
	  return;
	  break;
	case LAMPROJ2_:
	  return;
	  break;

	default:
	  handle_error (arg1, arg2, bek_cons_mismatch);
	}

      break;
    case LAM_:
      switch (((setif_term) arg2)->type)
	{
	case LAM_:
	  {
	    alabel_t_inclusion_ind (((struct lam_ *) arg1)->f0,
				    ((struct lam_ *) arg2)->f0);
	    argT_inclusion_ind_contra (((struct lam_ *) arg1)->f1,
				       ((struct lam_ *) arg2)->f1);
	    T_inclusion_ind (((struct lam_ *) arg1)->f2,
			     ((struct lam_ *) arg2)->f2);

	  }
	  break;
	case LAMPROJ0_:
	  alabel_t_inclusion_ind (((struct lam_ *) arg1)->f0,
				  ((struct lamProj0_ *) arg2)->f0);
	  break;
	case LAMPROJ1_:
	  argT_inclusion_ind_contra (((struct lam_ *) arg1)->f1,
				     ((struct lamProj1_ *) arg2)->f0);
	  break;
	case LAMPROJ2_:
	  T_inclusion_ind (((struct lam_ *) arg1)->f2,
			   ((struct lamProj2_ *) arg2)->f0);
	  break;
	case REFPROJ0_:
	  return;
	  break;
	case REFPROJ1_:
	  return;
	  break;
	case REFPROJ2_:
	  return;
	  break;

	default:
	  handle_error (arg1, arg2, bek_cons_mismatch);
	}

      break;

    default:
      return;
    }

  return;
}

void andersen_terms_init (void)
{
  engine_init ();
  setif_init ();
  setif_init ();
  flowrow_init ();
}

void andersen_terms_reset (void)
{
  engine_reset ();
  setif_reset ();
  setif_reset ();
  flowrow_reset ();
}

void andersen_terms_stats (FILE * arg1)
{
  engine_stats (arg1);
}

void andersen_terms_print_graph (FILE * arg1)
{
  print_constraint_graphs (arg1);
}

void andersen_terms_serialize (FILE * arg1, hash_table * arg2,
			       unsigned long arg3)
{
  return;
}

hash_table *andersen_terms_deserialize (FILE * arg1)
{
  return NULL;
}

void andersen_terms_region_serialize (FILE * arg1)
{
  return;
}

void andersen_terms_region_deserialize (translation arg1, FILE * arg2)
{
  return;
}