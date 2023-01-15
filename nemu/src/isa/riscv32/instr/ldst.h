def_EHelper(lw) {
  printf("lw : src1 is 0x%x\n", *dsrc1);
  printf("lw : src2 is 0x%x\n", id_src2->imm);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
  printf("lw : ddest is 0x%x\n", *ddest);
}

def_EHelper(sw) {
  printf("sw : src is 0x%x\n", *dsrc1);
  printf("sw : offset is 0x%x\n", id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
  printf("sw : ddest is 0x%x\n", *ddest);
}

