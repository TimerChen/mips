#ifndef CPU_H
#define CPU_H

#include <string>
#include <iostream>

class InsInput;
class mipsDebug;
class CPU
{
	friend class InsInput;
	friend class mipsDebug;
public:
	CPU(unsigned int MEMSIZE = 32*1024*1024,
		std::istream *In = &std::cin, std::ostream *Out = &std::cout);
	~CPU();

	const unsigned int MemSize;
	unsigned int pcTop;
	static const unsigned int InsStep;

	unsigned int &pc();
	unsigned int &hi();
	unsigned int &lo();
	unsigned int &ptop();

	void set_i(std::istream *i);
	void set_o(std::ostream *o);

	void write_reg(int idx, int val);
	unsigned int read_reg(int idx);
	void write_mem(int idx, int val,short len);
	unsigned int read_mem(int idx, short len);
	unsigned int write_memStr(int idx, const std::string &str, bool zero=1);
	std::string read_memStr(int idx);

	int read_ioInt();
	void write_ioInt( int val );
	int read_ioStr( int pos, unsigned int maxLen );
	void write_ioStr( const std::string &str );
	int newSpace( int len );

	void lockReg( int idx );
	void unlockReg( int idx );
	bool isFree( int idx );
	void lockPc();
	void unlockPc();
	bool isFree_pc();

	void clearLockReg();

private:

	char *Memory;
	//lo = reg[32] hi = reg[33] pc = reg[34]
	unsigned int reg[35],top;
	short locked[35];
	short locked_pc;
	std::istream *in;
	std::ostream *out;

};

#endif // CPU_H
