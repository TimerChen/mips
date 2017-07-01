#include <iostream>
#include <string>

#include "mips.h"

using namespace std;

Mips mips;

std::string getString( iostream& io )
{
	char cc[1024];
	std::string str;
	while( !io.eof() )
	{
		io.get( cc, 1000, '\0' );
		str = str + cc;
	}
	return str;
}

int main(int argc, char *argv[])
{
	//cout << "Hello World!" << endl;
	ifstream fin("test.in");
	ofstream fout("test.out");
	stringstream sout;
	try{
		mips.run(std::string("test.s"),&fin,&sout);
		//mips.run(std::string("test.s"),&fin,&cout);
	}catch( ... ){
		std::cerr << "Some error ocurred." << std::endl;
	}
	std::cerr << "\nOutput:\n";

	std::string str;
	str = getString( sout );
	cerr << str << endl;


	return 0;
}
