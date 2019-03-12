#ifndef __YUNOS_MODULE_H
#define __YUNOS_MODULE_H

#include <sys/types.h>

typedef int (*yunos_entry_t)(void );

#define __used     __attribute__((__used__))
#define __define_earlyinit(fn, id) \
        static yunos_entry_t __entry_##fn##id __used \
        __attribute__((__section__(".earlyentry" #id ".init"))) = (yunos_entry_t)fn;

#define __define_kernelinit(fn, id) \
        static yunos_entry_t __entry_##fn##id __used \
        __attribute__((__section__(".kernelentry" #id ".init"))) = (yunos_entry_t)fn;

#define __define_appinit(fn, id) \
        static yunos_entry_t __entry_##fn##id __used \
        __attribute__((__section__(".appentry" #id ".init"))) = (yunos_entry_t)fn;

#define __define_moduleexit(fn, id) \
        static yunos_entry_t __entry_##fn##id __used \
        __attribute__((__section__(".moduleentry" #id ".exit"))) = fn;

#define __define_exportsymbol(fn, id) \
        static yunos_entry_t __entry_##fn##id __used \
        __attribute__((__section__(".exportsymbol" #id ".export"))) = fn;

#define zhuque_early_init(fn)       __define_earlyinit(fn, 0)

#define yunos_core_init(fn)        __define_kernelinit(fn, 0)
#define yunos_arch_init(fn)        __define_kernelinit(fn, 1)
#define yunos_subsys_init(fn)      __define_kernelinit(fn, 2)
#define zhuque_device_init(fn)      __define_kernelinit(fn, 3)
#define yunos_postdevice_init(fn)  __define_kernelinit(fn, 4)
#define yunos_late_init(fn)        __define_kernelinit(fn, 5)

#define corelib_entry(fn)          __define_appinit(fn, 0)
#define lib_entry(fn)              __define_appinit(fn, 1)
#define coreapp_entry(fn)          __define_appinit(fn, 2)
#define app_entry(fn)              __define_appinit(fn, 3)

#define yunos_appcorelib_init(fn)  __define_appinit(fn, 0)
#define yunos_applib_init(fn)      __define_appinit(fn, 1)
#define yunos_appcore_init(fn)     __define_appinit(fn, 2)
#define yunos_app_init(fn)         __define_appinit(fn, 3)

#define yunos_module_init(fn)      __define_kernelinit(fn, 6)

#define yunos_module_exit(fn)      __define_moduleexit(fn, 0)

#define EXPORT_SYMBOL_NOUSED(fn)   __define_exportsymbol(fn, 0)

/****************************************************************************
 *
 * Description:
 *   module_execaddr: Module address in memory.
 *   module_len: Module length, including .bss.
 *   pinit: Module init function address.
 *   pexit: Module exit function address.
 *
 ****************************************************************************/

struct module_head_s {
    uint32_t magic_code;
    uint32_t is_loaded;
    uint32_t module_execaddr;
    uint32_t module_len;
    yunos_entry_t *pinit;
    yunos_entry_t *pexit;
} typedef module_head_t;

int yunos_init_static_module(void *module, uint32_t arg);
int yunos_delete_static_module(void *module);

#endif

