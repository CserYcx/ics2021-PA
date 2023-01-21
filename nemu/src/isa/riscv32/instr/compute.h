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

// div (signed)
def_EHelper(div){
  printf("div : src1 is 0x%x\n",*dsrc1);
  printf("div : src2 is 0x%x\n",*dsrc2);
  rtl_divs_q(s,ddest,dsrc1,dsrc2);
  printf("div : dest is 0x%x\n",*ddest);

}

// rem (signed)
def_EHelper(rem){
  printf("rem : src1 is 0x%x\n",*dsrc1);
  printf("rem : src2 is 0x%x\n",*dsrc2);
  rtl_divs_r(s,ddest,dsrc1,dsrc2);
  printf("rem : dest is 0x%x\n",*ddest);
}

// slt
def_EHelper(slt){
  printf("slt : src1 is 0x%x\n",*dsrc1);
  printf("slt : src2 is 0x%x\n",*dsrc2);
  rtl_setrelop(s,RELOP_LT,ddest,dsrc1,dsrc2);
  printf("sltu : dest is 0x%x\n",*ddest);

}

// slti (signed)
def_EHelper(slti){
  printf("slti : src1 is 0x%x\n",*dsrc1);
  printf("slti : src2 is 0x%x\n",(int32_t)id_src2->simm);
  // may be bug here(i don't treat the id_src2->imm as a signed numbers)
  rtl_setrelopi(s,RELOP_LT,ddest,dsrc1,id_src2->simm);
  printf("slti : dest is 0x%x\n",*ddest);
}

// sltiu (unsigned)
def_EHelper(sltiu){
  printf("sltiu : src1 is 0x%x\n",*dsrc1);
  printf("sltiu : src2 is 0x%x\n",id_src2->simm);
  rtl_setrelopi(s,RELOP_LTU,ddest,dsrc1,id_src2->simm);
  printf("slti : dest is 0x%x\n",*ddest);
}

// sltu (unsigned)
def_EHelper(sltu){
  printf("sltu : src1 is 0x%x\n",*dsrc1);
  printf("sltu : src2 is 0x%x\n",*dsrc2);
  rtl_setrelop(s,RELOP_LTU,ddest,dsrc1,dsrc2);
  printf("sltu : dest is 0x%x\n",*ddest);
}

def_EHelper(sll){
  printf("sll : src1 is 0x%x\n",*dsrc1);
  printf("sll : src2 is 0x%x\n",*dsrc2);
  rtl_sll(s,ddest,dsrc1,dsrc2);
  printf("sll : dest is 0x%x\n",*ddest);
}

def_EHelper(sra){
  printf("sra : src1 is 0x%x\n",*dsrc1);
  printf("sra : src2 is 0x%x\n",*dsrc2);
  rtl_sra(s,ddest,dsrc1,dsrc2);
  printf("sra : dest is 0x%x\n",*ddest);
}

def_EHelper(srl){
  printf("srl : src1 is 0x%x\n",*dsrc1);
  printf("srl : src2 is 0x%x\n",*dsrc2);
  rtl_srl(s,ddest,dsrc1,dsrc2);
  printf("srl : dest is 0x%x\n",*ddest);
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

// srli
def_EHelper(srli){
  if ((id_src2->imm & 0x20) == 0){
    printf("srli : shamt(src2) is 0x%x\n",id_src2->imm);
    printf("srli : src1 is 0x%x\n",*dsrc1);
    rtl_srli(s,ddest,dsrc1,id_src2->imm);
    printf("srli : dest is 0x%x\n",*ddest);
  }else{
    printf("the srli instruction is invalid");
  }
}

// srai 
def_EHelper(srai){
  if ((id_src2->imm & 0x20) == 0){
    printf("srai : shamt(src2) is 0x%x\n",id_src2->imm);
    printf("srai : src1 is 0x%x\n",*dsrc1);
    rtl_srai(s,ddest,dsrc1,id_src2->imm);
    printf("srai : dest is 0x%x\n",*ddest);
  }else{
    printf("the srai instruction is invalid");
  }

}

// move bit operation 
// xor (R-type)
def_EHelper(xor){
  printf("xor : src1 is 0x%x\n",*dsrc1);
  printf("xor : src2 is 0x%x\n",*dsrc2);
  rtl_xor(s,ddest,dsrc1,dsrc2);
  printf("xor : dest is 0x%x\n",*ddest);
}

// or (R-type)
def_EHelper(or){
  printf("or : src1 is 0x%x\n",*dsrc1);
  printf("or : src2 is 0x%x\n",*dsrc2);
  rtl_or(s,ddest,dsrc1,dsrc2);
  printf("or : dest is 0x%x\n",*ddest);
}

// and 
def_EHelper(and){
  printf("and : src1 is 0x%x\n",*dsrc1);
  printf("and : src2 is 0x%x\n",*dsrc2);
  rtl_and(s,ddest,dsrc1,dsrc2);
  printf("and : dest is 0x%x\n",*ddest);
}

// andi (I-type , immediate)
def_EHelper(andi){
  printf("andi : src1 is 0x%x\n",*dsrc1);
  printf("andi : src2 is 0x%x\n",id_src2->simm);
  rtl_andi(s,ddest,dsrc1,id_src2->simm);
  printf("or : dest is 0x%x\n",*ddest);
}

// xori (I-type , immediate)
def_EHelper(xori){
  printf("xori : src1 is 0x%x\n",*dsrc1);
  printf("xori : src2 is 0x%x\n",id_src2->simm);
  rtl_xori(s,ddest,dsrc1,id_src2->simm);
  printf("xori : dest is 0x%x\n",*ddest);
} 