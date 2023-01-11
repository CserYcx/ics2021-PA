//jal 
def_EHelper(jal){
    // in the rtl-basic.h
    // need to relocate the imm and move left 1 bit
    // simm is the offset signed-extended
    sword_t simm = (s->isa.instr.j.simm20 << 19) | (s->isa.instr.j.imm19_12) << 11
    | (s->isa.instr.j.imm11 << 10) | (s->isa.instr.j.imm10_1 ) ;
    simm = simm<<1;
    // if destion is 0(rz), jal is j instruction
    if(s->isa.instr.j.rd == 0){
        printf("j: jal = %x\n",simm);
        printf("next pc = %x\n",simm + s->pc);
        rtl_j(s,s->pc += simm);
    }
    else{
        printf("jal: simm = %x\n",simm);
        printf("next pc = %x\n",simm + s->pc);
        *ddest = s->pc+4;
        rtl_j(s,s->pc += simm);
    }
}

// jalr
def_EHelper(jalr){
    // (src1->imm + simm11_0) & 0xfffffffe -> pc
    *ddest = s->pc+4;
    s->pc = (*dsrc1+s->isa.instr.i.simm11_0) & 0xfffffffe;
    *dsrc1 = s->pc;
    printf("jalr: next pc = %x\n",s->pc);
    rtl_jr(s,dsrc1);
}