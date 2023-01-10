def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}

// addi
def_EHelper(addi){
  rtl_addi(s,ddest,dsrc1,id_src1->imm);
}

// auipc (immediate + pc -> dest)
def_EHelper(auipc){
  rtl_li(s,ddest,id_src1->imm+s->pc);
}
