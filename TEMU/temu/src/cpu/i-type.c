#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

/* decode I-type instrucion with unsigned immediate 
	src1 : 源寄存器
	src2 : 立即数（16位）
*/
static void decode_imm_type(uint32_t instr) {

	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	
	op_src2->type = OP_TYPE_IMM;
	op_src2->imm = instr & IMM_MASK;
	op_src2->val = op_src2->imm;

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RT_MASK) >> (IMM_SIZE);
}

make_helper(lui) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src2->val << 16);
	sprintf(assembly, "lui   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(ori) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = op_src1->val | op_src2->val;
	sprintf(assembly, "ori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(andi){
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & zero_extend(op_src2->imm));
	sprintf(assembly, "andi   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(xori){
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val ^ zero_extend(op_src2->imm));
	sprintf(assembly, "xori   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(addi){
	decode_imm_type(instr);
	if(IntegerOverflow(op_src1->val , sign_extend(op_src2->imm)) ){
		//未完成：处理异常
		sprintf(assembly, "addi	  %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
		panic("addi of\n");
		return;
	}
	reg_w(op_dest->reg) = (op_src1->val + sign_extend(op_src2->imm) );
	sprintf(assembly, "addi	  %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(addiu){
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val + sign_extend(op_src2->imm) );
	sprintf(assembly, "addiu	  %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(slti){
	decode_imm_type(instr);
	if( ((int)(op_src1->val)) < ((int)sign_extend(op_src2->imm)) ){
		reg_w(op_dest->reg) = 0x00000001;
	}
	else{
		reg_w(op_dest->reg) = 0x00000000;
	}
	sprintf(assembly, "slti	  %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(sltiu){
	decode_imm_type(instr);
	if( ((uint32_t)(op_src1->val)) < ((uint32_t)sign_extend(op_src2->imm)) ){
		reg_w(op_dest->reg) = 0x00000001;
	}
	else{
		reg_w(op_dest->reg) = 0x00000000;
	}
	sprintf(assembly, "sltiu	  %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}
