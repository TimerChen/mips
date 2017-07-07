#ifndef PREDICTOR_H
#define PREDICTOR_H


class Predictor
{
public:
	Predictor();

	//const static int BIT, BACK;

	//char mode[BIT][BACK],his[BIT];

	void fail();

	void step( const int &address, const char &next );
	bool predict( const int &address );

	double suc();
private:

	void move( const char &add, const char &next );
	char hash( const int &address );
	char mode[16][16],his[16];
	int tot,failed;
};

#endif // PREDICTOR_H
