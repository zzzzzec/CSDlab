#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

/* decode R-type instrucion */
static void decode_r_type(uint32_t instr) {
	//rs
	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	//rt
	op_src2->type = OP_TYPE_REG;
	op_src2->imm = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
	op_src2->val = reg_w(op_src2->reg);

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

make_helper(and){
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
	sprintf(assembly, "and   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(nor){
	decode_r_type(instr);
	reg_w(op_dest->reg) = (~(op_src1->val | op_src2->val));
	sprintf(assembly, "nor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(or){
	decode_r_type(instr);
	reg_w(op_dest->reg) = ((op_src1->val | op_src2->val));
	sprintf(assembly, "or   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(xor){
	decode_r_type(instr);
	reg_w(op_dest->reg) = ((op_src1->val ^ op_src2->val));
	sprintf(assembly, "xor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(add){
	decode_r_type(instr);
	if(IntegerOverflow(op_src1->val , op_src2 -> val)){
		sprintf(assembly, "add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
		panic("add of\n");
		return;
	}
	reg_w(op_dest->reg) = (op_src1->val + op_src2->val);
	sprintf(assembly, "add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(addu){
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val + op_src2->val);
	sprintf(assembly, "addu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sub){
	decode_r_type(instr);
	if(IntegerOverflow(op_src1->val , ~(op_src2->val) + 1)){
		sprintf(assembly, "sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
		panic("sub of\n");
		return;
	}
	reg_w(op_dest->reg) = (op_src1 ->val - op_src2->val);
	sprintf(assembly, "sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(subu){
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1 ->val - op_src2->val);
	sprintf(assembly, "subu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(slt){
	decode_r_type(instr);
	if(((int)(op_src1->val)) < ((int)(op_src2->val))){
		reg_w(op_dest->reg) = 0x00000001;
	}
	else{
		reg_w(op_dest->reg) = 0x00000000;
	}
	sprintf(assembly, "slt   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sltu){
	decode_r_type(instr);
	if(((uint32_t)(op_src1->val)) < ((uint32_t)(op_src2->val))){
		reg_w(op_dest->reg) = 0x00000001;
	}
	else{
		reg_w(op_dest->reg) = 0x00000000;
	}
	sprintf(assembly, "sltu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sllv){
	decode_r_type(instr);
	int offset = (op_src1->val)& 0x0000001f; 
	reg_w(op_dest->reg) = (op_src2->val) << offset; 
	sprintf(assembly, "sllv   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg),offset);
}

make_helper(sll){
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src2->val) << ((instr&SHAMT_MASK) >> FUNC_SIZE);
	sprintf(assembly, "sll   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg),((instr&SHAMT_MASK) >> FUNC_SIZE));
}

make_helper(div){
	decode_r_type(instr);
	if(op_src2->val == 0){
		sprintf(assembly, "div   %s,   %s   ASSERT : div 0 " , REG_NAME(op_src1->reg),REG_NAME(op_src2->reg) );
	}
	cpu.lo = ((int)(op_src1->val))/((int)(op_src2->val));
	cpu.hi = ((int)(op_src1->val))%((int)(op_src2->val));
	sprintf(assembly, "div   %s,   %s" , REG_NAME(op_src1->reg),REG_NAME(op_src2->reg) );
}

make_helper(divu){
	decode_r_type(instr);
	if(op_src2->val == 0){
		sprintf(assembly, "divu   %s,   %s   ASSERT : div 0 " , REG_NAME(op_src1->reg),REG_NAME(op_src2->reg) );
	}
	cpu.lo = ((uint32_t)(op_src1->val))/((uint32_t)(op_src2->val));
	cpu.hi = ((uint32_t)(op_src1->val))%((uint32_t)(op_src2->val));
	sprintf(assembly, "divu   %s,   %s" , REG_NAME(op_src1->reg),REG_NAME(op_src2->reg) );
}

make_helper(mult){
	//decode_r_type(instr);
	//uint64_t result = 
}
make_helper(multu){

}

make_helper(srav){

}
make_helper(sra){
	
}
make_helper(srlv){
	
}
make_helper(srl){
	
}

make_helper(jr){
	
}
make_helper(jalr){
	
}

make_helper(beq){
	
}
make_helper(bne){
	
}
make_helper(bgez){
	
}
make_helper(bgtz){
	
}
make_helper(blez){
	
}
make_helper(bltz){
	
}
make_helper(bgezal){
	
}
make_helper(bltzal){
	
}

make_helper(mfhi){
	
}
make_helper(mflo){
	
}
make_helper(mthi){
	
}
make_helper(mtlo){
	
}