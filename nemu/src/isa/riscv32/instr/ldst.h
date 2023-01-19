def_EHelper(lw) {
  printf("lw : offset is 0x%x\n", id_src2->imm);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
  printf("lw : ddest is 0x%x\n", *ddest);
}

// lbu (load 8 bit from the memory but then zero extended before storing in rd)
def_EHelper(lbu) {
  printf("lbu : offset is 0x%x\n", id_src2->imm);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 1);
  printf("lbu : ddest is 0x%x\n", *ddest);
}

// store word
def_EHelper(sw) {
  printf("sw : offset is 0x%x\n", id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}

// store 16-bit
def_EHelper(sh) {
  printf("sh : offset is 0x%x\n", id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 2);
}