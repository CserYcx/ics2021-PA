def_EHelper(lw) {
  printf("lw : offset is 0x%x\n", id_src2->imm);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
  printf("lw : ddest is 0x%x\n", *ddest);
}

def_EHelper(sw) {
  printf("sw : offset is 0x%x\n", id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}

// sh
def_EHelper(sh) {
  printf("sh : offset is 0x%x\n", id_src2->imm);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 2);
}