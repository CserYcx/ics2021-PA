def_EHelper(lw) {
  printf("instruction is %s\n",s->logbuf);
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
}

def_EHelper(sw) {
  printf("instruction is %s\n",s->logbuf);
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}

