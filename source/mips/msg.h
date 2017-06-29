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
	unsigned int arg[5];
};
class MsgEX
{

public:
	MsgEX();
	enum msgType{ r1 };
	short opt;
	unsigned int arg[7];
};

#endif // MSG_H
