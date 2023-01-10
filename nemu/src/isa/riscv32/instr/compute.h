def_EHelper(lui) {
  printf("lui: imm is 0x%x\n",id_src1->imm);
  rtl_li(s, ddest, id_src1->imm);
}

// addi
def_EHelper(addi){
  printf("addi : imm is 0x%x\n",id_src2->imm);
  sword_t simm = id_src2->imm << 20;
  rtl_addi(s,ddest,dsrc1,simm);
}

// auipc (immediate + pc -> dest)
def_EHelper(auipc){
  printf("auipc : imm is 0x%x\n",id_src1->imm);
  rtl_li(s,ddest,id_src1->imm+s->pc);
  printf("auipc : ddest is 0x%x\n",*ddest);
}
