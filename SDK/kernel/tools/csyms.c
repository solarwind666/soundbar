#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_SYM_NAME_LEN    128

typedef struct _sym_entry_t {
    unsigned long long addr;
    unsigned int len;
    unsigned int start_pos;
    unsigned char *sym;
}sym_entry;


static sym_entry *table;
static unsigned long long _stext = 0;
static unsigned int table_size = 0, table_cnt = 0;
static FILE *error_file = NULL;
static FILE *out_file = NULL;

static void output_error_msg(const char *msg, ...)
{
    FILE *out = stderr;
    va_list ap;

    if (error_file != NULL) {
        out = error_file;
    }

    va_start(ap, msg);
    vfprintf(out, msg, ap);
    va_end(ap);
}

static void output_str(const char *msg, ...)
{
    FILE *out = stdout;
    va_list ap;

    if (out_file != NULL) {
        out = out_file;
    }

    va_start(ap, msg);
    vfprintf(out, msg, ap);
    va_end(ap);

}

static void output_label(const char *label)
{
    output_str(".globl %s\n", label);
    output_str("\tALGN\n");
    output_str("%s:\n", label);
}


static void show_usage(void)
{
    output_error_msg("Usage: csyms < in.map > out.S\n");
    exit(1);
}

static int read_symbol(FILE *in, sym_entry *s)
{
    char str[500];
    char *sym, stype;
    int rc;

    rc = fscanf(in, "%llx %c %499s\n", &s->addr, &stype, str);
    if (rc != 3) {
        if (rc != EOF && fgets(str, 500, in) == NULL) {
            output_error_msg("Read error or end of file.\n");
        }
        return -1;
    }

    sym = str;

        /* Ignore most absolute/undefined (?) symbols. */
    if (strcmp(sym, "_stext") == 0) {
        _stext = s->addr;
    } else if (toupper(stype) == 'A') {
        return -1;
    } else if (toupper(stype) == 'U') {
        return -1;
    } else if (toupper(stype) == 'D' || toupper(stype) == 'B') {
    /* exclude data symbols */
        return -1;
    } else if (toupper(stype) == 'R') {
    /* exclude read only data symbols */
        return -1;
    } else if (str[0] == '$') {
    /* exclude ELF local symbols ($t, $d) */
        return -1;
    } else if (stype == 'N') {
    /* exclude debugging symbols */
        return -1;
    }

    /* include the type field in the symbol name, so that it gets
     * compressed together */
    s->len = strlen(str) + 1;
    s->sym = malloc(s->len + 1);
    if (!s->sym) {
        output_error_msg("csyms failure: "
            "unable to allocate required amount of memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy((char *)s->sym + 1, str);
    s->sym[0] = stype;

    return 0;
}


static void read_map(FILE *in)
{
    while (!feof(in)) {
        if (table_cnt >= table_size) {
            table_size += 10000;
            table = realloc(table, sizeof(*table) * table_size);
            if (!table) {
                output_error_msg("out of memory\n");
                exit (1);
            }
        }
        if (read_symbol(in, &table[table_cnt]) == 0) {
            table[table_cnt].start_pos = table_cnt;
            table_cnt++;
        }
    }
}
static void write_symbols(void)
{
    unsigned int i;

    output_str("#define PTR .long\n");
    output_str("#define ALGN .align 4\n");

    output_str("\t.section .rodata, \"a\"\n");

    output_label("__allsyms_addresses");
    for (i = 0; i < table_cnt; i++) {
        if (toupper(table[i].sym[0]) != 'A') {
            if (_stext <= table[i].addr) {
                output_str("\tPTR\t_stext + %#llx\t//%s\n",
                    table[i].addr - _stext, table[i].sym);
            } else {
                output_str("\tPTR\t_stext - %#llx\t//%s\n",
                    _stext - table[i].addr, table[i].sym);
            }
        } else {
            output_str("\tPTR\t%#llx\t//%s\n",
                    table[i].addr, table[i].sym);
        }
    }
    output_str("\n");

    output_label("__allsyms_num_syms");
    output_str("\tPTR\t%d\n", table_cnt);
    output_str("\n");

}

int main(int argc, char **argv)
{
    if (argc != 1) {
        show_usage();
    }

    read_map(stdin);
    write_symbols();
    return 0;
}
