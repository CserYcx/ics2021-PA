#include <cpu/decode.h>
#include "../local-include/rtl.h"

//what's that (you should remember this and then back to understand it)
#define INSTR_LIST(f) f(lui)  f(lw) f(sw) f(inv) f(nemu_trap) f(addi) f(auipc)

def_all_EXEC_ID();
