// beq
def_EHelper(beq){
    printf("beq : dsrc1 is 0x%x\n",*dsrc1);
    printf("beq : dsrc2 is 0x%x\n",*dsrc2);
    if(*dsrc1 == *dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 11)|(s->isa.instr.b.imm11 << 10)|
                   (s->isa.instr.b.imm10_5 << 6)|(s->isa.instr.b.imm4_1 << 1);
    printf("beq : offset is 0x%x\n",simm);
    printf("beq : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        printf("beq : src1 not equal to src2\n");
    }
}

// bne
def_EHelper(bne){
    printf("bne : dsrc1 is 0x%x\n",*dsrc1);
    printf("bne : dsrc2 is 0x%x\n",*dsrc2);
    if(*dsrc1 == *dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 11)|(s->isa.instr.b.imm11 << 10)|
                   (s->isa.instr.b.imm10_5 << 6)|(s->isa.instr.b.imm4_1 << 1);
    printf("bne : offset is 0x%x\n",simm);
    printf("bne : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        printf("bne : src1 not equal to src2\n");
    }
}