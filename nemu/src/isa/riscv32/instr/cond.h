//jal 
def_EHelper(jal){
    // in the rtl-basic.h
    sword_t simm = (s->isa.instr.j.simm20 << 19) | (s->isa.instr.j.imm10_1 << 10) |
                 (s->isa.instr.j.imm11 << 8) | (s->isa.instr.j.imm19_12);
    printf("imm20 = %x\n",s->isa.instr.j.simm20);
    printf("imm10 = %x\n",s->isa.instr.j.imm10_1);
    printf("imm11 = %x\n",s->isa.instr.j.imm11);
    printf("imm19 = %x\n",s->isa.instr.j.imm19_12);
    printf("simm = %x\n",simm);
    *ddest = s->pc+4;
    rtl_j(s,s->pc += simm);
}

// jalr
/*
def_EHelper(jalr){
    rtl_j;
}*/