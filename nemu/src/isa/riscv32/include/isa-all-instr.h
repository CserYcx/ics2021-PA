#include <cpu/decode.h>
#include "../local-include/rtl.h"

//what's that (you should remember this and then back to understand it)
#define INSTR_LIST(f) f(lui) f(lw) f(lh) f(lbu) f(lhu) f(sw) f(sh) f(sb) f(inv) f(nemu_trap) f(addi) f(slt) f(sra) f(srl) f(slti) f(sltiu) f(sltu) f(sll) f(slli) f(srli) f(srai) f(auipc) f(jal) f(jalr) f(add) f(sub) f(mul) f(mulh) f(div) f(rem) f(beq) f(bne) f(bge) f(blt) f(bltu) f(xor) f(xori) f(or) f(and) f(andi)

def_all_EXEC_ID();
