def_EHelper(lui) {
  printf("lui: imm is 0x%x\n",id_src1->imm);
  rtl_li(s, ddest, id_src1->imm);
}

// addi
def_EHelper(addi){
  printf("addi : imm is 0x%x\n",id_src1->imm);
  printf("addi : dsrc1 is 0x%x\n",*dsrc1);
  rtl_addi(s,ddest,dsrc1,id_src1->imm);
}

// auipc (immediate + pc -> dest)
def_EHelper(auipc){
  printf("auipc : imm is 0x%x\n",id_src1->imm);
  rtl_li(s,ddest,id_src1->imm+s->pc);
  printf("auipc : ddest is 0x%x\n",*ddest);
}
