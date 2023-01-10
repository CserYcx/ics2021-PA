//jal 
def_EHelper(jal){
    // in the rtl-basic.h
    sword_t simm = (s->isa.instr.j.simm20 << 19) | (s->isa.instr.j.imm10_1 << 9) |
                 (s->isa.instr.j.imm11 << 8) | (s->isa.instr.j.imm19_12);
    simm = simm>>8;
    printf("simm = %x\n",simm);
    *ddest = s->pc+4;
    rtl_j(s,s->pc += simm);
}

// jalr
/*
def_EHelper(jalr){
    rtl_j;
}*/