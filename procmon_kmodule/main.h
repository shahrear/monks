#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <asm/page.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>

#include <linux/mm.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sysctl.h>
#include <linux/fdtable.h>
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/proc_fs.h>

/*****************************************************************************\
| In case we are on IA32 system we need to get the identifier for both x64    |
| and x86 archs. And we can't do that only with #include <asm/unistd.h>       |
| because this way we'll only get the identifiers of one of the archs, the    |
| one that we're currently compiling on.                                      |
| Also, even if we could trick somehow the compiler to include both           |
| identifiers, there is another problem: we will get different values with    |
| the same name.                                                              |
| Example: __NR_read and __NR_read, both have the same name, but on           |
| x86 it's value is N, while on x64 it's value is M. That's why we need to do |
| some magic.                                                                 |
| When we're on x64 and ia32 emulation is enabled, we'll search for the       |
| <asm/unistd_32.h> file, replace all "__NR_xxx" with "_NR32_xxx" and then    |
| use them for the ia32 syscall table.                                        |
\*****************************************************************************/

#ifdef CONFIG_IA32_EMULATION
#include "unistd_32.h"
#endif

#include "utils.h"
#include "sct_hook.h"

/*****************************************************************************\
| Define if debugging is enabled or disabled                                  |
\*****************************************************************************/

#define debug 1

#if debug == 1
#define DEBUG(...) printk(__VA_ARGS__);
#else
#define DEBUG(...)
#endif

/*****************************************************************************\
|                                      END                                    |
\*****************************************************************************/

void activate(void);
void deactivate(void);
int is_active(void);

int register_procmon_sysctl(void);
void unregister_procmon_sysctl(void);

#endif