#include <cpu/decode.h>
#include "../local-include/rtl.h"

//what's that (you should remember this and then back to understand it)
#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(sh) f(inv) f(nemu_trap) f(addi) f(slti) f(sltiu) f(sltu) f(slli) f(srai) f(auipc) f(jal) f(jalr) f(add) f(sub) f(div) f(rem) f(beq) f(bne) f(bge) f(blt) f(bltu) f(xor) f(or) f(andi)

def_all_EXEC_ID();
