#ifndef MSG_H
#define MSG_H


class MsgIF
{
public:
	MsgIF(const char *Str = "");
	char str[12];
};
class MsgID
{
public:
	MsgID();
	short opt,narg;
	int arg[5];
};
class MsgEX
{

public:
	MsgEX();
	enum msgType{ non,r1,r2lh,r2j,load,store,oInt,oStr,iInt,iStr,space,exit,exit0 };
	short opt;
	int arg[2];
};
class MsgMEM
{
public:
	MsgMEM();
	int idx, arg;
};

#endif // MSG_H
