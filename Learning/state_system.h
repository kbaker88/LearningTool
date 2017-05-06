#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

class State
{
public:
	State() : MathSet(false), EnglishSet(false),
		ActiveModule(0) {}
	~State() {}

	int Words[2] = {};
	int Numbers[3] = {};
	bool MathSet, EnglishSet;
	unsigned char ActiveModule;

private:
};

#endif