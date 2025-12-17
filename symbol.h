#ifndef symbol_defined
#define symbol_defined

typedef struct Symbol {
         char *name ;
         short type ;
         union {
               int    len;
               char   *str;
               char   cval;
               int    ival;
               long long  lval;
               long double val;
               long double (*ptr)(long double);
               int    (*iptr)(void*);
         } u ;
  struct Symbol *next ;
} Symbol ;

/* FIX */
#define SYM_UNDEF   0
#define SYM_VAR     1
#define SYM_BUILTIN 2
#define SYM_IBUILTIN 3
#define SYM_STRVAR  4
/* FIX */

void    init_sym(void);
void    dump_sym(void);
Symbol *lookup_sym(const char *s);
Symbol *install_sym(const char *s, int t, long double d);

#endif
