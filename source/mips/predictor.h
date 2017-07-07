#ifndef PREDICTOR_H
#define PREDICTOR_H


class Predictor
{
public:
	Predictor();
	char mode[16][16],his[16];
	void move( const char &add, const char &next );
	char hash( const unsigned int &address );

	void step( const unsigned int &address, const char &next );
	bool predict( const unsigned int &address );
};

#endif // PREDICTOR_H
