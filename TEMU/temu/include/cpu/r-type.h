#ifndef __RTYPE_H__
#define __RTYPE_H__

make_helper(and);
make_helper(nor);
make_helper(or);
make_helper(xor);

make_helper(add);
make_helper(addu);

make_helper(sub);
make_helper(subu);

make_helper(slt);
make_helper(sltu);

make_helper(div);
make_helper(divu);

make_helper(mult);
make_helper(multu);

make_helper(sllv);
make_helper(sll);
make_helper(srav);
make_helper(sra);
make_helper(srlv);
make_helper(srl);

make_helper(jr);
make_helper(jalr);

make_helper(beq);
make_helper(bne);
make_helper(bgez);
make_helper(bgtz);
make_helper(blez);
make_helper(bltz);
make_helper(bgezal);
make_helper(bltzal);

make_helper(mfhi);
make_helper(mflo);
make_helper(mthi);
make_helper(mtlo);

#endif
