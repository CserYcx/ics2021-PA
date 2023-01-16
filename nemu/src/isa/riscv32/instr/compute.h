def_EHelper(lui) {
  printf("lui: imm is 0x%x\n",id_src1->imm);
  rtl_li(s, ddest, id_src1->imm);
}

// I should provide the li
/*
def_EHelper(li){
  printf("li : imm is 0x%x\n",id_src2->imm);
  sword_t simm = id_src2->imm << 20;
  rtl_addi(s,ddest,rz,simm);
  printf("addi : ddest is 0x%x\n",*ddest);
}*/

// addi
def_EHelper(addi){
  printf("addi : imm is 0x%x\n",id_src2->imm);
  sword_t simm = id_src2->imm ;
  rtl_addi(s,ddest,dsrc1,simm);
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

// slti
def_EHelper(slti){
  printf("slti : src1 is 0x%x\n",*dsrc1);
  printf("slti : src2 is 0x%x\n",*dsrc2);
  if(*dsrc1 < *dsrc2){
    rtl_li(s,ddest,0);
  }else{
    rtl_li(s,ddest,1);
  }
  printf("slti : dest is 0x%x\n",*ddest);
}
