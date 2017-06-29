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
	enum msgType{ non,r1,r2lh,r2j,load,store, };
	short opt;
	int arg[7];
};

#endif // MSG_H
