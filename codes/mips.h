#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

//Instruction Set
class IS;
//Instruction Fetch
class IF;
//Instruction Decode
class ID;
//Execute
class EX;
//Memory Access
class MEM;
//Write Back
class WB;
class IS
{
public:
	//IS(const std::string file = ""){}
	IS(){}
	void readFile(const std::string file)
	{
		fstream fin(file, ios::in);
		if(fin.is_open())
		{

			fin.close();
		}
	}

};
class IF
{
public:
	IF(const std::string file = "");
private:

public:


};
class ID
{


};

