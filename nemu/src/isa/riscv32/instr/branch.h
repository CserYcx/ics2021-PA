// beq
def_EHelper(beq){
    //printf("beq : dsrc1 is 0x%x\n",*dsrc1);
    //printf("beq : dsrc2 is 0x%x\n",*dsrc2);
    if(*dsrc1 == *dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 12)|(s->isa.instr.b.imm11 << 11)|
                   (s->isa.instr.b.imm10_5 << 5)|(s->isa.instr.b.imm4_1 << 1);
    //printf("beq : offset is 0x%x\n",simm);
    //printf("beq : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        //printf("beq : src1 not equals to src2\n");
    }
}

// bne
def_EHelper(bne){
    //printf("bne : dsrc1 is 0x%x\n",*dsrc1);
    //printf("bne : dsrc2 is 0x%x\n",*dsrc2);
    if(*dsrc1 != *dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 12)|(s->isa.instr.b.imm11 << 11)|
                   (s->isa.instr.b.imm10_5 << 5)|(s->isa.instr.b.imm4_1 << 1);
    //printf("bne : offset is 0x%x\n",simm);
    //printf("bne : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        //printf("bne : src1 equals to src2\n");
    }
}

// bge (signed)
def_EHelper(bge){
    //printf("bge : dsrc1 is 0x%x\n",*dsrc1);
    //printf("bge : dsrc2 is 0x%x\n",*dsrc2);
    if((int32_t)*dsrc1 >= (int32_t)*dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 12)|(s->isa.instr.b.imm11 << 11)|
                   (s->isa.instr.b.imm10_5 << 5)|(s->isa.instr.b.imm4_1 << 1);
    //printf("bge : offset is 0x%x\n",simm);
    //printf("bge : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        //printf("bge : src1 not greater than src2\n");
    }
}

// blt (signed)
def_EHelper(blt){
    //printf("blt : dsrc1 is 0x%x\n",*dsrc1);
    //printf("blt : dsrc2 is 0x%x\n",*dsrc2);
    if((int32_t)*dsrc1 < (int32_t)*dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 12)|(s->isa.instr.b.imm11 << 11)|
                   (s->isa.instr.b.imm10_5 << 5)|(s->isa.instr.b.imm4_1 << 1);
    //printf("blt : offset is 0x%x\n",simm);
    //printf("blt : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        //printf("blt : src1 not less than src2\n");
    }
}

// bltu (unsigned)
def_EHelper(bltu){
    //printf("bltu : dsrc1 is 0x%x\n",*dsrc1);
    //printf("bltu : dsrc2 is 0x%x\n",*dsrc2);
    if(*dsrc1 < *dsrc2){
    sword_t simm = (s->isa.instr.b.simm12 << 12)|(s->isa.instr.b.imm11 << 11)|
                   (s->isa.instr.b.imm10_5 << 5)|(s->isa.instr.b.imm4_1 << 1);
    //printf("bltu : offset is 0x%x\n",simm);
    //printf("bltu : next pc is 0x%x\n",s->pc + simm);
        rtl_j(s,s->pc += simm);
    }else{
        //printf("bltu : src1 not less than src2\n");
    }
}