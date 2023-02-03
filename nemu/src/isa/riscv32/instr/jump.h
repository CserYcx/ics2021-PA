//jal 
def_EHelper(jal){
    // in the rtl-basic.h
    // need to relocate the imm and move left 1 bit
    // simm is the offset signed-extended
    sword_t simm = (s->isa.instr.j.simm20 << 19) | (s->isa.instr.j.imm19_12) << 11
    | (s->isa.instr.j.imm11 << 10) | (s->isa.instr.j.imm10_1 ) ;
    simm = simm<<1;
    *ddest = s->pc+4;
    rtl_j(s,s->pc += simm);
    
}

// jalr
def_EHelper(jalr){
    // (src1->imm + simm11_0) & 0xfffffffe -> pc
    *ddest = s->pc+4;
    s->pc = (*dsrc1+id_src2->imm) & 0xfffffffe;
    //printf("jalr: next pc = %x\n",s->pc);
    rtl_j(s,s->pc);
}

