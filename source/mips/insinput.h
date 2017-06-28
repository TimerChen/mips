#ifndef INSINPUT_H
#define INSINPUT_H

#include "cpu.h"

#include <vector>
#include <map>
#include <sstream>

class InsInput
{
public:
	InsInput(CPU *cpuName);

	void initialize(const std::string &file);
private:

	enum tokenType{label,pinst,inst,alabel,num,str,reg};

	CPU *cpu;
	unsigned int ptr;
	std::string buffer;
	std::vector<std::string> lines;
	std::map<std::string, unsigned int> labels;
	std::map<std::string, short> regs, insts, pinsts;
	std::stringstream ss;

	void clearBuffer();
	void readFile(const std::string &file);
	std::string getLine();
	std::string getWord(const std::string &line, unsigned int &i, short &type, const bool &isArg=0 );
	int translate( const std::string &a, const short &type );

	void initRegs();
	void initPInst();
	void initInst();

	void setTop();
	void putData();
	void putInst();

	void makeIns();

};
#endif // INSINPUT_H
