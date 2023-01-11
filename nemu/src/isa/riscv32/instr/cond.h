//jal 
def_EHelper(jal){
    // in the rtl-basic.h
    // need to relocate the imm and move left 1 bit
    sword_t simm = (s->isa.instr.j.simm20 << 19) | (s->isa.instr.j.imm19_12) << 11
    | (s->isa.instr.j.imm11 << 10) | (s->isa.instr.j.imm10_1 ) ;
    /*
    printf("jal: imm20 is %x\n",s->isa.instr.j.simm20<<19);
    printf("jal: imm19 is %x\n",s->isa.instr.j.imm19_12<<11);
    printf("jal: imm11 is %x\n",s->isa.instr.j.imm11<<2);
    printf("jal: imm10 is %x\n",s->isa.instr.j.imm10_1);
    */
    simm = simm<<1;
    printf("jal: simm = %x\n",simm);
    printf("next pc = %x\n",simm + s->pc);
    *ddest = s->pc+4;
    rtl_j(s,s->pc += simm);
}

// jalr
def_EHelper(jalr){
    *ddest = s->pc+4;
    s->pc = (*dsrc1+s->isa.instr.i.simm11_0) & 0xfffffffe;
    *dsrc1 = s->pc;
    printf("jalr: next pc = %x\n",s->pc);
    rtl_jr(s,dsrc1);
}