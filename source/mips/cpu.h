#ifndef CPU_H
#define CPU_H

#include <string>

class InsInput;

class CPU
{
	friend class InsInput;
public:
	CPU(unsigned int MEMSIZE = 32*1024*1024);
	~CPU();

	const unsigned int MemSize;
	static const unsigned int InsStep;

	unsigned int &pc();
	unsigned int &hi();
	unsigned int &lo();

	void set_io(const std::string &file);

	void write_reg(int idx, int val);
	unsigned int read_reg(int idx,short len);
	void write_mem(int idx, int val, short len);
	unsigned int read_mem(int idx, short len);
	unsigned int write_memStr(int idx, const std::string &str, bool zero=1);
	std::string read_memStr(int idx);

	int read_ioInt();
	void write_ioInt();
	std::string read_ioStr();
	void write_ioStr();

private:

	char *Memory;
	//lo = reg[32] hi = reg[33] pc = reg[34]
	unsigned int reg[35],top;
	bool locked[25];
	std::string ioFile;

};

#endif // CPU_H
