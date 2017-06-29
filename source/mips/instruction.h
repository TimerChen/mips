#ifndef INSTRUCTION_H
#define INSTRUCTION_H


struct Instruction
{
	enum Inst{add,addu,addiu,sub,subu,mul,mulu,div,divu,xor0,xoru,neg,negu,rem,remu,li,seq,sge,sgt,sle,slt,sne,b,beq,bne,bge,ble,bgt,blt,beqz,bnez,blez,bgez,bgtz,bltz,j,jr,jal,jalr,la,lb,lh,lw,sb,sh,sw,move,mfhi,mflo,nop,syscall,mul2,mulu2,div2,divu2};
	enum Pinst{align,ascii,asciiz,byte,half,word,space,data,text};
	Instruction();
		/*const unsigned short &OPT=0, const unsigned short &ARG0=0,
		const unsigned int &ARG1=0, const unsigned int &ARG2=0 );*/
	unsigned char opt,arg0,arg1,arg2;
	unsigned int arg3,arg4;
	unsigned int to_int0();
	void set_int0( int val );
};

#endif // INSTRUCTION_H
