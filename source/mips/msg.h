#ifndef MSG_H
#define MSG_H


class Msg0
{
public:
	Msg0(const char *Str = "");
	~Msg0();
	char *str;

};
class Msg1
{
public:
	short opt,len;
	unsigned int arg[3];
};

#endif // MSG_H
