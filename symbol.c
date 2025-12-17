/* symbol.c - Symbol Table Management */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "hocdecl.h"
#include "symbol.h"
#include "pcalc.h"
/* -------- Globals: ----------------------------------------------------- */

static Symbol *symlist = 0;     /* symbol table: linked list */

/* -------- Builtin Functions: ------------------------------------------- */

static struct {
    char *name;
    long double (*func)(long double);
} builtins[] = {
    {"sin",      sinl},
    {"cos",      cosl},
    {"atan",     atanl},
    {"log",      Log},
    {"log10",    Log10},
    {"exp",      Exp},
    {"sqrt",     Sqrt},
    {"int",      integer},
    {"abs",      fabsl},
    {"f2c",      f2c},
    {"c2f",      c2f},
    {"in2mm",    in2mm},
    {"mm2in",    mm2in},
    {"po2kg",    po2kg},
    {"kg2po",    kg2po},
    {0,          0}
};

static struct {
    char *name;
    long double (*func)(long double);
} builtins_upper[] = {
    {"SIN",      sinl},
    {"COS",      cosl},
    {"ATAN",     atanl},
    {"LOG",      Log},
    {"LOG10",    Log10},
    {"EXP",      Exp},
    {"SQRT",     Sqrt},
    {"INT",      integer},
    {"ABS",      fabsl},
    {"F2C",      f2c},
    {"C2F",      c2f},
    {"IN2MM",    in2mm},
    {"MM2IN",    mm2in},
    {"PO2KG",    po2kg},
    {"KG2PO",    kg2po},
    {0,          0}
};

/* -------- Internal Builtins: ------------------------------------------- */

static int ddate_wrapper(void *arg) {
    return ddate((const char *)arg);
}

static int print_wrapper(void *arg) {
    long double val = *(long double *)arg;
    return print(val);
}

static int echo_wrapper(void *arg) {
    return echo((const char *)arg);
}

static int echo_nl_wrapper(void *arg) {
    return echo_nl((const char *)arg);
}

static struct {
    char *name;
    int (*ifunc)(void *);
} ibuiltins[] = {
    {"date",     ddate_wrapper},
    {"print",    print_wrapper},
    {"echo",     echo_wrapper},
    {"_echo",    echo_nl_wrapper},
    {0,          0}
};

static struct {
    char *name;
    int (*ifunc)(void *);
} ibuiltins_upper[] = {
    {"DATE",     ddate_wrapper},
    {"PRINT",    print_wrapper},
    {"ECHO",     echo_wrapper},
    {"_ECHO",    echo_nl_wrapper},
    {0,          0}
};

/* -------- INIT_SYM ---------------------------------------------------- */

void init_sym(void)
{
    int i;
    Symbol *s;

    /* Initialize builtins */
    for (i = 0; builtins[i].name; i++) {
        s = install_sym(builtins[i].name, BUILTIN, 0.0);
        s->u.ptr = builtins[i].func;
    }

    for (i = 0; builtins_upper[i].name; i++) {
        s = install_sym(builtins_upper[i].name, BUILTIN, 0.0);
        s->u.ptr = builtins_upper[i].func;
    }

    /* Initialize internal builtins */
    for (i = 0; ibuiltins[i].name; i++) {
        s = install_sym(ibuiltins[i].name, IBUILTIN, 0.0);
        s->u.iptr = ibuiltins[i].ifunc;
    }

    for (i = 0; ibuiltins_upper[i].name; i++) {
        s = install_sym(ibuiltins_upper[i].name, IBUILTIN, 0.0);
        s->u.iptr = ibuiltins_upper[i].ifunc;
    }
}

/* -------- LOOKUP_SYM --------------------------------------------------- */

Symbol *lookup_sym(const char *s)        /* find s in symbol table */
{
    Symbol *sp;
    for (sp = symlist; sp != (Symbol *)0; sp = sp->next)
        if (strcmp(sp->name, s) == 0)
            return sp;
    return 0;                   /* 0 ==> not found */
}

/* -------- INSTALL_SYM -------------------------------------------------- */

Symbol *install_sym(const char *s, int t, long double d) /* install s in symbol table */
{
    Symbol *sp;
    char *emalloc(unsigned);

    sp = (Symbol *)emalloc(sizeof(Symbol));
    sp->name = emalloc(strlen(s) + 1); /* +1 for '\0' */
    strcpy(sp->name, s);
    sp->type = t;
    sp->u.val = d;
    sp->next = symlist;         /* put at front of list */
    symlist = sp;
    return sp;
}

/* -------- DUMP_SYM ----------------------------------------------------- */

void dump_sym(void)
{
    Symbol *sp;

    for (sp = symlist; sp != (Symbol *)0; sp = sp->next) {
        printf("%s: ", sp->name);
        switch (sp->type) {
        case VAR:
            printf("VAR = %Lf\n", sp->u.val);
            break;
        case BUILTIN:
            printf("BUILTIN\n");
            break;
        case IBUILTIN:
            printf("IBUILTIN\n");
            break;
        case UNDEF:
            printf("UNDEF\n");
            break;
        default:
            printf("type %d\n", sp->type);
        }
    }
}

/* -------- EMALLOC ------------------------------------------------------ */

char *emalloc(unsigned n)
{
    char *p;
    p = malloc(n);
    if (p == 0)
        execerror("out of memory", (char *)0);
    return p;
}
