#include <iostream>
#include <string>

#include "mips.h"

using namespace std;

Mips mips;

int main(int argc, char *argv[])
{
	//cout << "Hello World!" << endl;
	ifstream fin("test.in");
	ofstream fout("test.out");
	try{
		mips.run(std::string("test.s"),&fin,&cout);
	}catch( ... ){
		std::cerr << "Some error ocurred." << std::endl;
	}
	return 0;
}
