#include <iostream>
#include <string>

#include "mips.h"
#include "debug.h"

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
	string name = "bulgarian-5110379024-wuhang";
	ifstream fin( name + ".in" );
	ofstream fout( name + ".out" );
	stringstream sout;

	const bool sOut = 0, fOut = 0, cOut = 1;

	if( argc > 1 )
		mipsDebug::debugMode = 0;
	else
		mipsDebug::debugMode = 1;

	if( mipsDebug::debugMode )
		cerr << "\t- Debug Mode Now -\n";

	mipsDebug::insInputInformation = 1;
	mipsDebug::stepInformation = 1;
	mipsDebug::stepInformation_detail = 1;
	mipsDebug::returnInformation = 1;

	try{
		if(mipsDebug::debugMode)
		{
			if( sOut ){

				mips.run(std::string( name + ".s" ),&fin,&sout);

			}else if( fOut )
			{
				mips.run(std::string( name + ".s" ),&fin,&fout);
			}else if( cOut ){
				mips.run(std::string( name + ".s" ),&fin,&cout);
			}
		}else{
			mipsDebug::insInputInformation = 0;
			mipsDebug::stepInformation = 0;
			mipsDebug::stepInformation_detail = 0;
			mipsDebug::returnInformation = 0;

			mips.run(std::string( argv[1] ),&cin,&cout);
		}

	}catch( ... ){
		std::cerr << "Some error ocurred." << std::endl;
	}
	if( sOut && mipsDebug::debugMode )
	{
		std::cerr << "\nOutput:\n";

		std::string str;
		str = getString( sout );
		cerr << str << endl;
	}


	return 0;
}
