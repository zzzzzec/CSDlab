#include "common.h"
#include "helper.h"

uint32_t sign_extend(uint32_t imm){
	if((imm & 0x00008000)){
		imm = imm | 0xffff0000; //第15位是1，用1拓展
		return imm;
	}
	return imm;
}

uint32_t zero_extend(uint32_t imm){
	return (imm & 0x0000ffff);
}

int IntegerOverflow(int x,int y){
   if(x < 0 && y < 0 && x+y > 0){
	   return 1;
   }
   if(x > 0 && y > 0 && x+y < 0){
	   return 1;
   }
   return 0;
}