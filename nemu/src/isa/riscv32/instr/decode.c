#include "../local-include/reg.h"
#include <cpu/ifetch.h>
#include <isa-all-instr.h>

def_all_THelper();

static uint32_t get_instr(Decode *s) {
  return s->isa.instr.val;
}

// decode operand helper
#define def_DopHelper(name) \
  void concat(decode_op_, name) (Decode *s, Operand *op, word_t val, bool flag)

static def_DopHelper(i) {
  op->imm = val;
}

// op pointer used to represent id_src1, id_src2 or id_dest
static def_DopHelper(r) {
  bool is_write = flag;
  static word_t zero_null = 0;
  // If flag is false or val(the register in instruction) is 0, return 0(simulate the x0)
  // Else, record the address of the register
  op->preg = (is_write && val == 0) ? &zero_null : &gpr(val);
}

// Decode Helper Function
// To further decode, concretely to know like:
// what's the immediate, which register to load
// I-type: imm[11:0], rs1 5, funct3 3, rd 5, opcode 7
// Here we find the rs, rd and immediate, then we go to use the DopHelper
static def_DHelper(I) {
  // the source registers(src1, src2) and the destination register(dest)
  decode_op_r(s, id_src1, s->isa.instr.i.rs1, false);
  decode_op_i(s, id_src2, s->isa.instr.i.simm11_0, false);
  decode_op_r(s, id_dest, s->isa.instr.i.rd, true);
}

static def_DHelper(U) {
  decode_op_i(s, id_src1, s->isa.instr.u.imm31_12 << 12, true);
  decode_op_r(s, id_dest, s->isa.instr.u.rd, true);
}

// Maybe has a bug here: why all the flag state is true
static def_DHelper(J){
  decode_op_i(s, id_src1, s->isa.instr.j.imm19_12 & 0x000ff000, true);
  decode_op_i(s, id_src1, s->isa.instr.j.imm11 & 0x00000800, true);
  decode_op_i(s, id_src1, s->isa.instr.j.imm10_1 & 0x00000402, true);
  decode_op_i(s, id_src1, s->isa.instr.j.imm20 & 0x00010000, true);
  decode_op_r(s, id_dest, s->isa.instr.j.rd, true);
}

static def_DHelper(S) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t simm = (s->isa.instr.s.simm11_5 << 5) | s->isa.instr.s.imm4_0;
  decode_op_i(s, id_src2, simm, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}

// The THelper function is to make sure which type of the instruction
// The example is use the funt3(010) to confirm is lw
def_THelper(load) {
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", lw);
  return EXEC_ID_inv;
}

def_THelper(store) {
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", sw);
  return EXEC_ID_inv;
}

// li THelper

def_THelper(li) {
  //            imm[11:0]      rs1   func3 rd    opcode
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", addi);
  //def_INSTR_TAB("??????? ????? ????? ??? ????? 01101 11", lui);
  return EXEC_ID_inv;
}

// I write some comment to make me understand the structure of the instruction deeper
// The U-type: imm[31:12], rd, opcode (The lui is an example)
// lui: is to load higher 20-bits to the dest register and the lower 12-bits filled with zero
def_THelper(main) {
  // Macro expansion is like the decode_type(example: decode_U)
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00000 11", I     , load);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01000 11", S     , store);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01101 11", U     , lui);

  /**
   *Here are my complementary instructions
  **/
  // li instruction (Pseudo, need to be extended  Fixed:maybe not, just use the addi to implement)
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00100 11", I     , li);
  // auipc instruction(Add Upper Immediate to pc)
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00101 11", U     , auipc);
  // jal instruction
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 11011 11", J     , jal);
  
  def_INSTR_TAB  ("??????? ????? ????? ??? ????? 11010 11",         nemu_trap);
  // Macro expansion is like table_lui, return EXEC_ID_lui
  // A little confuse here: where use the inv?
  return table_inv(s);
};

int isa_fetch_decode(Decode *s) {
  s->isa.instr.val = instr_fetch(&s->snpc, 4);
  // return the index to repetory the g_exec_table
  int idx = table_main(s);
  return idx;
}

/* The PA2 task steps:
 * 1.In "nemu/src/isa/$ISA/instr/decode.c", adding the true matching rules(Sreach the RISCV-32 manual)
 * 2.Use the RTL to complete the correct EHelper(Notice the Calling Convention)
 * 3.Add the instruction into the "nemu/src/isa/$ISA/include/isa-all-instr.h"
 * 4.Maybe you should add some header file in "nemu/src/isa/$ISA/include/isa-exec.h"
 */