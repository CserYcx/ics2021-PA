def_EHelper(lui){
  printf("lui: imm is 0x%x\n",id_src1->imm);
  rtl_li(s, ddest, id_src1->imm);
}


// addi
def_EHelper(addi){
  printf("addi : imm is 0x%x\n",id_src2->simm);
  rtl_addi(s,ddest,dsrc1,id_src2->simm);
  printf("addi : ddest is 0x%x\n",*ddest);
}

// auipc (immediate + pc -> dest)
def_EHelper(auipc){
  printf("auipc : imm is 0x%x\n",id_src1->imm);
  rtl_li(s,ddest,id_src1->imm+s->pc);
  printf("auipc : ddest is 0x%x\n",*ddest);
}

// add (src1 + src2 -> dest)
def_EHelper(add){
  printf("add : src1 is 0x%x\n",*dsrc1);
  printf("add : src2 is 0x%x\n",*dsrc2);
  rtl_add(s,ddest,dsrc1,dsrc2);
  printf("add : dest is 0x%x\n",*ddest);
}

// sub 
def_EHelper(sub){
  printf("sub : src1 is 0x%x\n",*dsrc1);
  printf("sub : src2 is 0x%x\n",*dsrc2);
  rtl_sub(s,ddest,dsrc1,dsrc2);
  printf("sub : dest is 0x%x\n",*ddest);
}

// slti (signed)
def_EHelper(slti){
  printf("slti : src1 is 0x%x\n",*dsrc1);
  printf("slti : src2 is 0x%x\n",(int32_t)id_src2->simm);
  // may be bug here(i don't treat the id_src2->imm as a signed numbers)
  if(*dsrc1 < (int32_t)id_src2->simm){
    rtl_li(s,ddest,1);
  }else{
    rtl_li(s,ddest,0);
  }
  printf("slti : dest is 0x%x\n",*ddest);
}

// sltiu (unsigned)
def_EHelper(sltiu){
  printf("sltiu : src1 is 0x%x\n",*dsrc1);
  printf("sltiu : src2 is 0x%x\n",id_src2->simm);
  if(*dsrc1 < id_src2->simm){
    rtl_li(s,ddest,1);
  }else{
    rtl_li(s,ddest,0);
  }
  printf("slti : dest is 0x%x\n",*ddest);
}

// slli (I-type)
def_EHelper(slli){
  // shamt[5] == 0, the instruction is valid
  if ((id_src2->imm & 0x20) == 0){
    printf("slli : shamt(src2) is 0x%x\n",id_src2->imm);
    printf("slli : src1 is 0x%x\n",*dsrc1);
    rtl_slli(s,ddest,dsrc1,id_src2->imm);
    printf("slli : dest is 0x%x\n",*ddest);
  }else{
    printf("the slli instruction is invalid");
  }
}
